#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>

int size;
char *ptr=NULL;
char *author=NULL;

int getinp(char * buffer, int len) {
    int retval = read(0, buffer, len);
    if ( retval == -1)
        exit(0);
    if (*(buffer+retval-1) == '\n')
        *(buffer+retval-1) = '\0';
    return 0;
}

int getint()
{
    char buffer[32];
    getinp(buffer, 32);
    return atoi(buffer);
}

sem_t sema;

void sig()
{
  sem_post(&sema);
  sleep(1);
  sem_wait(&sema);
  return;
}

// void *run(void* n)
// {
//   sem_wait(&sema);
//   alarm(5);
//   signal(SIGALRM,sig);
//   printf("Enter Size %d: ",*(int*)n);
//   size=getint();
//   ptr=malloc(size);
//   printf("Enter Data %d: ",*(int*)n);
//   getinp(ptr,size);
//   printf("Data %d= %s\n",*(int*)n,ptr);
//   sem_post(&sema);
// }



void run(int n)
{
  char auth[0x100];
  sem_wait(&sema);
  alarm(4);
  signal(SIGALRM,sig);
  do
  {
    printf("\nEnter Size %d: ",n);
    size=getint();
  }while(size<=0 || size>1000);
  ptr=malloc(size);
  printf("\nEnter Author name : ");
  getinp(auth,0xf0);
  author=strdup(auth);
  printf("\nEnter Data %d: ",n);
  getinp(ptr,size);
  printf("\nData entered\n");
  sem_post(&sema);
}

void* thread()
{
  run(2);
}

void alloc()
{
  int no;
  printf("How many chunks at a time (1/2) ? ");
  no=getint();
  if(no<=0 || no>2)
  {
    puts("invalid no!!");
    exit(0);
  }
  sem_init(&sema,0,1);
  pthread_t tid;
  pthread_t tid1;
  if(no==2)
  {
      pthread_create(&tid1, NULL, thread, NULL);
  }
  run(1);
  if(no==2)
    pthread_join(tid1,NULL);
}

void edit()
{
  if(!ptr)
    return;
  puts("Edit the last entered data:");
  printf("Enter new data: ");
  getinp(ptr,size);
}

int printmenu()
{
    puts("-----------------------");
    puts("#### @******@ Menu ####");
    puts("-----------------------");
    puts("| 1. alloc            |");
    puts("| 2. edit             |");
    puts("| 3. Exit             |");
    puts("-----------------------");
    printf("Enter choice >> ");
    return getint();
}

int initialise()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}


int main()
{
  initialise();
  sem_init(&sema,0,1);
  do
  {
        switch(printmenu())
        {
            case 1: alloc(); break;
            case 2: edit(); break;
            case 3: exit(0);
            default: puts("Invalid"); break;
        }
  }while(1);
  return 0;
}
