#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define SIZE 0x100

void print();

char * input;
struct ECHO{
  char buffer[SIZE-4];
  void (*ptr)();
};

struct ECHO echo;
void print()
{
  write(1,echo.buffer,SIZE-4);
  exit(0);
}

void initialise()
{

  alarm(60);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  echo.ptr=&print;
  uint32_t seed = 0 ;

  FILE * fp = NULL;
  fp = fopen("/dev/urandom","r");

  fread((char *)&seed,sizeof(uint32_t),1,fp);
  fclose(fp);
  srand(seed);

  input = (char * )(rand() & ~0xfff);
  mmap((void * )input,0x1000,PROT_READ | PROT_WRITE ,  MAP_ANONYMOUS | MAP_PRIVATE ,-1,0);
}

  void get_inp(char * buffer)
  {
    int i = 0;
    while(i<SIZE)
      {
        if(read(0,buffer + i , 1) ==-1)
          {exit(1);}
        if(*(buffer + i)=='\n')
          {
            *(buffer + i) = 0;
          return;
        }
      i++;
    }
  return;
}

int validate_input(char * buf)
{
  int i=0;
  for (;i<SIZE-0x4 && buf[i]!='\x00' ;i++)
    if( ! ( (buf[i]>=0x30 && buf[i]<=0x39) || (buf[i]>=0x41 && buf[i]<=0x5a) || ( buf[i]>=0x61 && buf[i] <=0x7a)))
      {
        puts("Invalid Input .");
        exit(0);
      }
  return i;
}

int main()
{
  initialise();
  
  puts("Welcome to echo v1.0");
  get_inp(input);
  validate_input(input);
  strcpy(echo.buffer,input);


  echo.ptr();
  return 0;
}
