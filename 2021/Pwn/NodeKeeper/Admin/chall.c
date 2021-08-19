/*  gcc chall.c -o chall */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>

typedef struct Node{
    struct Node * next;
    unsigned int len;
    char * buf;
}Node;

Node * Table[10]={0};
unsigned int CountArr[10]={0};

void Err(char * str){
    unsigned int len = strlen(str);
    write(1,str,len);
    exit(0);
}

void View(int);

void initialize(){
    setvbuf(stdin,0,_IONBF,0);
    setvbuf(stdout,0,_IONBF,0);
    setvbuf(stderr,0,_IONBF,0);
    alarm(300);
    return;
}

void handler(){
    Err("Timeout");
}

void getInp(char *buf, unsigned int len){
   int ret = read(0,buf,len) ;
   if(ret<=0){
       Err("Read error");
   }
   buf[ret-1]='\0';
   return;
}

unsigned int getInt(){
    char buf[5];
    getInp(buf,5);
    return atoi(buf);
}

unsigned int menu(){
    puts("---------------------------------");
    puts("|          Node Keeper          |");
    puts(" ------------------------------- ");
    puts("| 1. Add                        |");
    puts("| 2. Remove                     |");
    puts("| 3. Link                       |");
    puts("| 4. Unlink                     |");
    //puts("| 5. Merge                      |");
    puts("| 5. Exit                       |");
    puts(" -------------------------------");
    printf("Choice >> ");
    return getInt();
}

void Add(){
    int i=0;
    int totalCount=0;
    for(int j=0;j<10;j++){
        totalCount+=CountArr[j];
    }
    if(totalCount>=10){
        Err("Can't add");
    }
    for(i=0;i<10;i++){
        if(!Table[i]){
            break;
        }
    }
    if(i>=10){
        Err("No more space available");
    }
    printf("Enter length : ");
    unsigned int len = getInt();
    if(len<=0 || len>0x60){
        Err("Invalid size");
    }
    char * buf = malloc(len);
    Node * new = malloc(sizeof(Node));
    new->next=NULL;
    new->len = len;
    new->buf = buf;
    printf("Enter data : ");
    getInp(buf,len);
    CountArr[i]=1;
    Table[i]=new;
    puts("Success");
    return;
}

void Remove(){
    printf("Enter index: ");
    unsigned int idx = getInt();
    if(!Table[idx]){
        Err("Invalid index");
    }
    View(idx);
    printf("Which one?(1337 for all) ");
    unsigned int offset = getInt();
    if(offset<=0  || offset>CountArr[idx]){
        if(!(offset==1337))
            Err("Invalid offset");
    }
    offset--;
    Node * head = Table[idx];
    if(offset==1336){
        while(head!=NULL){
            Node * tmp=head->next;
            if(!head->buf)
                Err("Error");
            free(head->buf);
            head->next=NULL;
            head->buf=NULL;
            free(head);
            head=tmp;
        }
        Table[idx]=NULL;
        CountArr[idx]=0;
    }
    else if(offset==0){
        if(CountArr[idx]>1){
            Table[idx] = head->next;
            CountArr[idx]--;
        }
        else{
            Table[idx]=NULL;
            CountArr[idx]=0;
        }
        if(!head->buf)
            Err("Error");
        free(head->buf);
        head->next=NULL;
        head->buf=NULL;
        free(head);
    }
    else if(offset>0 && offset<CountArr[idx]){
        int check=1;
        while(check<offset){
            head = head->next;
            check++;
        }
        Node *tmp = head->next;
        head->next = head->next->next;
        CountArr[idx]--;
        if(!tmp->buf)
            Err("Error");
        free(tmp->buf);
        free(tmp);
    }
    else{
        Err("Invalid offset");
    }
    puts("Success");
    return;
}

void View(int idx){
    int offset=0;
    Node * head = Table[idx];
    while(offset<CountArr[idx]){
        Node * tmp=head->next;
        printf("Node %d Offset %d : %s\n",idx, offset+1, head->buf);
        offset++;
        head=tmp;
    }
    return;
}

void Unlink(){
    printf("Enter index: ");
    unsigned int idx = getInt();
    if(!Table[idx]){
        Err("Invalid index");
    }
    if(CountArr[idx]==1){
        Err("Can't unlink with only one chunk");
    }
    View(idx);
    printf("Enter offset: ");
    unsigned int offset = getInt();
    Node * head = Table[idx];
    Node *tmp=NULL;
    if(offset<=0 || offset>CountArr[idx])
        Err("Invalid offset");
    offset--;
    if(offset==0){
        if(CountArr[idx]>1){
            tmp = head;
            Table[idx] = head->next;
            CountArr[idx]--;
        }
    }
    else{
        int check=1;
        while(check<offset){
            head = head->next;
            check++;
        }
        tmp = head->next;
        head->next = head->next->next;
        CountArr[idx]--;
    }
    if(CountArr[idx]==0){
        Table[idx]=NULL;
    }
    //tmp->next=NULL;
    printf("Do you want to keep it (y/n)? ");
    char option;
    getInp(&option,2);
    if(option=='y' || option=='Y'){
        int i;
        for(i=0;i<10;i++){
            if(!Table[i])
                break;
        }
        if(i>=10)
            Err("No more space available");
        Table[i]=tmp;
        CountArr[i]=1;
    }
    else{
        free(tmp->buf);
        tmp->next=NULL;
        tmp->buf=NULL;
        free(tmp);
    }
    puts("Success");
    return;
}

void Link(){
    printf("Enter to index: ");
    unsigned int to = getInt();
    if(!Table[to]){
        Err("Invalid index");
    }
    printf("Enter from index: ");
    unsigned int from = getInt();
    if(!Table[from]){
        Err("Invalid index");
    }
    if(from==to){
        Err("Can't link Node to itself");
    }
    if(CountArr[to]==10 || (CountArr[to]+CountArr[from])>10)
        Err("Can't link");
    Node * From = Table[from];
    Node * To = Table[to];
    int count = 1;
    while(count<CountArr[to]){
        To = To->next;
        count++;
    }
    To->next = From;
    Table[from]=NULL;
    CountArr[to]+=CountArr[from];
    CountArr[from]=0;
    puts("Success");
    return;
}

/* 
void Merge(){
    printf("Enter index: ");
    unsigned int idx = getInt();
    if(!Table[idx]){
        Err("Invalid index");
    }
    Node * head = Table[idx];
    unsigned int totalSize =0;
    int count = 0;
    while(count<CountArr[idx]){
        int len = strlen(head->buf);
        if(len>head->len)
            len = head->len;
        totalSize+=len;
        head = head->next;
    }
    if(totalSize>0x400){
        Err("Size too large");
    }
    char * buf = malloc(totalSize+10);
    Node * new = malloc(sizeof(Node));
    new->buf = buf;
    new->next = NULL;
    new->len = totalSize;
    count = 0;
    head = Table[idx];
    while(count<CountArr[idx]){
        Node * tmp = head->next;
        int len = strlen(head->buf);
        if(len>head->len)
            len = head->len;
        strncpy(buf,head->buf,len);
        buf+=len;
        free(head->buf);
        free(head);
        head = tmp;
        count++;
    }
    Table[idx]=new;
    CountArr[idx]=1;
    return;
}
*/


int main(){
    initialize();
    signal(SIGALRM,handler);
    while(1){
        unsigned int option = menu();
        switch(option){
            case 1: Add(); break;
            case 2: Remove(); break;
            case 3: Link(); break;
            case 4: Unlink(); break;
                    //case 5: Merge(); break;
            case 5: Err("Bye");
            default: puts("Invalid Choice");
        }
    }
}
