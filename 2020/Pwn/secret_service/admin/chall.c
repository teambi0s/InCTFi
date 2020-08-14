#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <seccomp.h>
#include <sys/prctl.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/random.h>
#include <time.h>
#include <sys/uio.h>
#include <pthread.h>

unsigned int enrolled = 0;
unsigned int hacked = 0;
char* enrolled_table[3] = {0};
unsigned int is_enrolled[3] = {0};
unsigned int sizes[3] = {0};               
int size;
char ch;

//Redirecting stdout to /dev/null avoid leaks in vuln printf

unsigned int supress_stdout() {
  fflush(stdout);
  unsigned int ret = dup(1);
  int nullfd = open("/dev/null", O_WRONLY);
  // check nullfd for error omitted
  dup2(nullfd, 1);
  close(nullfd);
  return ret;
}

//Redirecting stderr to /dev/null
unsigned int supress_stderr()
{
    fflush(stderr);
    unsigned int ret = dup(2);
    int nullfd = open("/dev/null",O_WRONLY);
    dup2(nullfd,2);
    close(nullfd);
    return ret;
}

//Loading Thread Control Block , which stores canary
unsigned long init_0()
{
    asm("mov %fs:0,%rax");
}

void Exit()
{
    puts("Tata Bye Bye!");
    exit(EXIT_FAILURE);
}

//Standard get_inp function
unsigned int getInp(char* buf, unsigned int size) {
    unsigned int bytes_read = read(STDIN_FILENO,buf,size);
    if(bytes_read<=0)
    {
        puts("Read failed!");
        Exit();
    }
    if(buf[bytes_read-1]=='\n')
        buf[bytes_read-1] = '\0';
    return bytes_read;
}

void get_inp(char* buf, unsigned int size) {
    do {
        read(0,buf,1);
        size--;
    } while(size!=0 && *(buf++)!='\n');
    if(*(--buf)=='\n')
        *buf='\0';
}

//Standard get_int function
unsigned int getInt(){
  char buf[32];
  getInp(buf,31);
  return atoi(buf);
}

//Create a new thread to handle feedback request
void create_feedback()
{
    char feedback[100];
    puts("A new thread has been created for feedback");
    if((unsigned long)&feedback < init_0())
    {
        printf("Enter size of feedback: ");
        scanf("%d",&size);
        printf("Enter feedback: ");
        if(size>0x70)
        {
            puts("Size too large");
            Exit();
        }
        unsigned int fd_stdout = supress_stdout();
        unsigned int fd_stderr = supress_stderr();
        get_inp(feedback,size);
    }
    puts("Thank you!");
    return;
}

//Thread entry function which calls create_feedback
void *thread_entry(void *arg)
{
    create_feedback();
    return (void *)NULL;
}

//Enroll with the use of safe calloc
void Enroll()
{
    if(enrolled<=2)
    {
        printf("Enter Enrollment Index : ");
        unsigned int index = getInt(),size; 
        if(is_enrolled[index] || index < 0 || index > 2)
        {
            puts("Invalid or already enrolled!");
            return;
        }
        printf("Enter size : ");
        size = getInt();
        if(size<0x7f || size>=65530)
        {
            puts("Size not allowed!");
            Exit();
        }
        sizes[index] = size;
        puts("Enter your details -> ");
        char *details = (char *)calloc(sizes[index],1);
       // printf("Allocation happened at -> %llx\n",details); Debug info , dont mind
        getInp(details,sizes[index]);
        enrolled_table[index] = details;
        is_enrolled[index] = 1;
        enrolled++;
        puts("Ok! You are enrolled now");
        return;
    }
    else
    {
        puts("No more enrollments allowed!");
    }
}

//Safe view function
void View()
{
    printf("Enter index of the Enrolled Candidate: ");
    unsigned int index = getInt();
    if(!enrolled_table[index] || !is_enrolled[index] || index<0 || index > 2)
    {
        puts("Invalid Index!");
        return;
    }
    //printf("Viewing chunk %llx\n",enrolled_table[index]);
    printf("Details of Candidate %u: %s\n",index,enrolled_table[index]);
    return;
}

//Lets u hack the last byte of size by adding 1 to it, callable only twice
void Hack()
{
    if(hacked>1)
    {
        puts("No more hacking allowed!");
        return;
    }
    printf("Enter index of Enrolled Candidate: ");
    unsigned int index = getInt();
    if(!enrolled_table[index] || index<0 || index > 2)      
    {                                  
        puts("Invalid Index!");        
        return;                        
    }
    char* hack_addr = enrolled_table[index] - 8;
    //printf("Hacking chunk %llx\n",hack_addr);
    *(hack_addr) +=1;
    hacked++;
    return;
}

//Remove function , nulls out the is_enrolled bit , but doesnt null out the table
void Remove()
{
    printf("Enter index of Enrolled Candidate: ");
    unsigned int index = getInt();
    if(!enrolled_table[index] || !is_enrolled[index] || index<0 || index > 2)
    {
        puts("Invalid Index");
        return;
    }
    //printf("Removing chunk %llx\n",enrolled_table[index]);
    if(enrolled_table[index])
        free(enrolled_table[index]);
    is_enrolled[index]=0;
    enrolled--;
    return;
}

unsigned int menu()
{
  char string[] =
  "\n        Secret Service       \n"
  "+-----------------------------+\n"
  "| 1. Enroll Yourself          |\n"
  "| 2. View Your Details        |\n"
  "| 3. Remove Yourself          |\n"
  "| 4. Move on                  |\n"
  "| 5. Quit Service             |\n"
  "+-----------------------------+\n";
  printf("%s",string);
  printf("Your Choice >> ");
  return getInt();
}

//Wrapper around mprotect
void MProtect(long *region)
{
    if(mprotect(region,0x1000,1) != 0)
    {
        puts("MProtect failed");
        Exit();
    }
}
//%n is allowed in format string , but u cant write large numbers (greater than 0x900) with %n
void check_num(char *p)
{
    while (*p) 
    { 
        if ( isdigit(*p)) 
        {
            long val = strtol(p, &p, 10); 
            if(val>0x900)
            {
                puts("Not allowed");
                Exit();
            }
        } 
        else
            p++;
    }
    return;
}

//Secret service , which is intended to provide leaks and the final TCB overwrite
void secret_service()
{
    
    pthread_t t1;
    while(1)
    {
        unsigned int option = menu();
        switch(option)
        { 
            case 1: Enroll();
            break;
            case 2: View();
            break;
            case 3: Remove();
            break;
            case 4: goto Move_On;
            break;
            case 2020: Hack();
            break;
            case 5: exit(EXIT_SUCCESS);
        }
    }
    Move_On:
    puts("Do u want to leave a feedback for the service?(y/n)");
    scanf("%c",&ch);
    if(!strcmp(&ch,"y"))
    {
        pthread_create(&t1,NULL,thread_entry,NULL);
        pthread_join(t1,NULL);
    }
    else
    {
        puts("Thank you!");
    }
    exit(EXIT_SUCCESS);
}

//Generates a random 2 byte constraint which has to be mimicked for exploit
void get_rand(long *region)
{
    time_t toc;
    unsigned int tic = time(&toc),end_t;
    do{
    srand(tic/60);
    unsigned int lower = 0x1000 , upper = 0xffff;
    unsigned int rand_num = (rand()%(upper-lower+1)) + lower;
    unsigned int delay = rand()%300 + 1;
    end_t = tic + delay;
    tic = tic + delay;
    srand(end_t/30);
    unsigned int rand_num_2 = (rand()%(upper-lower+1)) + lower;
    memset(region,0,4);
    memcpy(region,&rand_num_2,2);
    *(long *)region &= (unsigned long)rand_num;
    }
    while(*(long *)region<0x1000);
    MProtect(region);
}

//Wrapper around mmap
long* Mmap()
{
    size_t pagesize = getpagesize();
    long *region = mmap(
        (void*) (pagesize * (1 << 20)),   
        pagesize,                        
        PROT_READ|PROT_WRITE,            
        MAP_ANON|MAP_PRIVATE,            
        0,
        0
    );
    if (region == MAP_FAILED) 
    {
        puts("mmap failed!");
        Exit();
    }
    return region;
}

//resume_stdout after suppressing to continue with program execution
void resume_stdout(int fd) {
  fflush(stdout);
  dup2(fd, 1);
  close(fd);
}

//init 
void initialize(){
  setvbuf(stdin,NULL,_IONBF,0);
  setvbuf(stdout,NULL,_IONBF,0);
  setvbuf(stderr,NULL,_IONBF,0);
  alarm(0x3c);
}

//Seccomp sandbox , allows , openat, read (only from fd 0) ,write(only to fd 1) , dup2 among few others
static void sandbox(void)
{
    prctl(PR_SET_NO_NEW_PRIVS, 1); // No root access possible
    //Allowing a few syscalls
    scmp_filter_ctx ctx;          
    ctx = seccomp_init(SCMP_ACT_KILL);
    if (!ctx) {
		puts("seccomp_init() error");
		exit(EXIT_FAILURE);
	}
    seccomp_rule_add(ctx,SCMP_ACT_ALLOW,SCMP_SYS(exit),0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 1,SCMP_A0(SCMP_CMP_EQ, 0));
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 1,SCMP_A0(SCMP_CMP_EQ, 1));
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(dup), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fcntl), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(nanosleep), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(clock_nanosleep	),0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(dup2), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(alarm), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(writev), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(clone), 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_robust_list), 0);
    seccomp_load(ctx);
}

//wrapper around vuln printf
void Print(char *name)
{
    check_num(name);
    unsigned int fd = supress_stdout();
    printf(name);
    resume_stdout(fd);
}

int main()
{
    char name[18];
    unsigned long age;
    unsigned long* age_ptr;
    initialize();
    sandbox();
    long *region = Mmap();
    puts("Hello there ! Why are you here?");
    get_rand(region);
    printf("Name: ");
    getInp(name,25);
    printf("Age: ");
    age = getInt();
    age_ptr = &age;
    puts("Hold on while I redirect u to the secret service!");
    sleep(1);
    Print(name);
    if(*(unsigned long *)region==*(unsigned long *)age_ptr)
    {
        secret_service();
    }
    else
    {
        puts("Nah you're a kiddo!");
        Exit();
    }
    return 0;
}
