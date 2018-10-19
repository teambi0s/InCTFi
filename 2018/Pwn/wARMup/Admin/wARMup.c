#include <stdio.h>
#include <unistd.h>

int main()
{
  alarm (30);
  setvbuf(stdout, NULL, _IONBF, 0);
  char buf[100];
  puts("Welcome to bi0s CTF!");

  read(0, &buf, 120);

  return 0;
}
