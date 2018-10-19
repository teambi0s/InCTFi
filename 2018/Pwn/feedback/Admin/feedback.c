#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX 4

typedef struct draft {
    char title[32];
    unsigned long size;
    char *feedback;
}draft;

draft table[MAX];
char* name=NULL;
FILE* fp=NULL;
int saved=0;

int get_inp(char * buffer, int len) {
    int retval = read(0, buffer, len);
    if ( retval == -1)
        exit(0);
    if (*(buffer+retval-1) == '\n')
        *(buffer+retval-1) = '\0';
    return 0;
}

int getint() {
    char buffer[32];
    get_inp(buffer, 32);
    return atoi(buffer);
}

long long getll() {
    char buffer[32];
    get_inp(buffer, 32);
    return atoll(buffer);
}

void update_name()
{
    if(name==NULL){
      name=(char*)malloc(132);
    }
    printf("Enter Name: ");
    get_inp(name,137);
}

void add_draft()
{
  int i=0;
  draft* ptr;
  unsigned long size;
  for(;table[i].feedback && i<MAX;i++);
  if(i>=MAX){
    puts("Draft Limit Exceeded !!");
    return;
  }
  ptr=&table[i];
  printf("Draft ID: %d\n",i);
  printf("Enter draft title: ");
  get_inp(ptr->title,0x20);
  printf("Enter size of draft: ");
  size=getll();
  printf("Give your feedback: ");
  if(size>0x500){
    ptr->feedback=(char*)malloc(0x500);
    get_inp(ptr->feedback,0x500);
  }
  else if(size < 0x80){
    ptr->feedback=(char*)malloc(0x80);
    get_inp(ptr->feedback,size);
  }
  else{
    ptr->feedback=(char*)malloc(size);
    get_inp(ptr->feedback,size);
  }
  ptr->size=size;
}

void view()
{
  if(name){
    printf("Author Name: %s\n",name);
  }
  puts("");
  for(int i=0;i<MAX;i++){
    if(table[i].feedback){
      printf("Draft No.: %d\n",i);
      printf("Title: %s\n",table[i].title);
      printf("Size: %lu\n",table[i].size);
      printf("Feedback: %s\n",(table[i].feedback));
      puts("");
    }
  }
}


void create()
{
  if(saved){
    printf("Sorry, only 1 feedback per team !!!\n");
    return;
  }
  fp=fopen("/home/feedback/ctffeedback","w");
  if (!fp)
	exit(0);
  puts(" [*] feedback created. You can now save your draft.");
}

void terminate()
{
  printf("Thank you for taking your time. Before submitting, please confirm that you are not a robot.\n");
  srand(time(NULL));
  int captcha = 1000+(rand()%9000);
  int inp;
  char* msg=malloc(0x40);
  sprintf(msg,"Enter this captcha code: %d",captcha);
  puts(msg);
  fflush(stdout);
  scanf("%d",&inp);
  if(inp!=captcha){
    puts("We don't want automatic feedback!!!!");
    exit(0);
  }
  if(name)
    free(name);
  puts("\n**** Feedback successfully submitted ****");
  exit(0);
}


void save()
{
  if(fp==NULL){
    puts("Create a Feedback first !!");
    return;
  }
  int id=-1;
  while(id<0 || id>=MAX || !table[id].feedback){
    printf("Enter draft id to save: ");
    id=getint();
  }
  printf(" [*] Saving draft no. %d....\n",id);
  fprintf(fp, "%s", table[id].feedback);
  free(table[id].feedback);
  table[id].feedback=NULL;
  fclose(fp);
  puts("Feedback successfully saved. We will get back to you soon !");
  puts("Since this is not an annonymous feedback, we need some of your deails.");

  char opt[2];
  char* team=malloc(0x3c8);
  char* details=team+0x350;
  memset(team,0,0x350);
  do{
    printf("Enter Team Name and Details: ");
    get_inp(team,0x350);
    puts("");
    printf("Team: %s\nConfirm? <y/n>: ",team);
    get_inp(opt,2);
    puts("");
  }while(opt[0]=='n');

  memset(team+0x350,0,120);
  printf("Now give us your contact details: ");
  get_inp(details,0x18);

  terminate();
}

int initialise()
{
  alarm(60);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
}

int printmenu()
{
    puts("-----------------------");
    puts("#### Feedback Menu ####");
    puts("-----------------------");
    puts("| 1. Leave your name  |");
    puts("| 2. Add a draft      |");
    puts("| 3. View Drafts      |");
    puts("| 4. Create Feedback  |");
    puts("| 5. Save Draft       |");
    puts("| 6. Exit             |");
    puts("-----------------------");
    printf("Enter choice >> ");
    return getint();
}


int main()
{
  initialise();
  puts("Enjoying our CTF? Do leave us a feedback........");
  do {
        switch(printmenu()) {
            case 1: update_name(); break;
            case 2: add_draft(); break;
            case 3: view(); break;
            case 4: create();break;
            case 5: save();break;
            case 6: exit(0);
            default: puts("Invalid"); break;
        }
    }while(1);
    return 0;
}

void asd() {
/* code */
}
