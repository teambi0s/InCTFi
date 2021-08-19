#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct player{
    char *name;
    int atk;
    int hp;
} Player;

typedef struct NPC{
    char *name;
    int hp;
    int idx;
    int size ;
} Npc;

typedef struct Master{
    void (*fnptr)();
    char *arg;
} master;

void useful_fn(){
    system("echo 'hello'");
}

void init(){
	setvbuf(stdout, NULL, _IONBF, 0);
	gid_t gid = getegid();
	setresgid(gid, gid, gid);
}

unsigned int MAXALLOC = 5;
Player *p = NULL;
Npc *players[0x10];
int cnt = 0 ;
int mergecnt = 0;

void get_str(char *buf, int sz){
    int ret = read(0,buf,sz);
    if(ret <= 0 ){
        puts("Error ");
        exit(0);    
        }
    int len = strlen(buf);
    if (buf[len-1] == 0xa){
        buf[len-1] = 0x0;
    }

}

int battle(int idx){
    if (!players[idx]){
        puts("There's no one here to battle ");
        return 0;
    }
    printf("Starting battle with %s ....\n",players[idx]->name);
    if(players[idx]->hp > 0)
        players[idx]->hp = players[idx]->hp - p->atk  ; 

    printf("\n[*] Health remaining : %d\n", players[idx]->hp);
    
    if (players[idx]->hp < 0 ){

        int choice = 0;
        printf("You beat 'em!\n1.kill\n2.spare\n>>");

        scanf("%d", &choice);

        if (choice == 1 ){
            puts("killed");

            free(players[idx]);
            free(players[idx]->name);
            
            players[idx] = NULL;
            return 0 ;      
        }
        puts("spared their lives ");
    }
    puts("\nthey aint dead yet !");
    return 0 ;   

}   

int playeralloc(){
    if (cnt > MAXALLOC){
        puts("too many allocations !!");
        return 0;
    }
    players[cnt] = (Npc*)malloc(sizeof(Npc));

    int size = 0x0;
    printf("Enter the size : ");
    scanf("%d", &size);
    if (size > 0x70){
        puts("Too large ! ");
        exit(1);
    }
    char * npcname = (char *)malloc(size);
    printf("Enter name : ");
    get_str(npcname, size);

    players[cnt]->name = npcname;
    players[cnt]->idx = cnt;
    players[cnt]->hp = 100;
    players[cnt]->size = size;
    cnt++;
    return 0;
}

char * buggy_strncat(char * dest, const char * src, size_t n){
    size_t dest_len = strlen(dest);
    size_t i;

    for (i =0 ; i< n ; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\x00';

    return dest;
}

int merge(int id1, int id2){
    
    int sz1 = players[id1]->size;
    int sz2 = players[id2]->size;

    if (id1 == id2 || sz1 != sz2 || sz1+sz2 >=0x60){
        printf("Dont try anything funny \n");
        exit(1);
    }
    players[id1]->name = realloc(players[id1]->name,sz1+sz2);
    players[id1]->size = sz1+sz2;
    players[id1]->hp = players[id1]->hp + players[id2]->hp;
    
    buggy_strncat(players[id1]->name,players[id2]->name,sz1+sz2);
    free(players[id2]->name);
    free(players[id2]);

    players[id2] = NULL;

    return 0;
}

int selectmerge(){
    
    if (mergecnt == 0){
        puts("Select 2 enemies to merge ");
        printf("[+] Enemy id 1: ");
        int id1;
        scanf("%d", &id1);
        printf("[+] Enemy id 2: ");
        int id2;
        scanf("%d", &id2);

        if( id1 >= 0  && id2 >= 0 && id1 <= cnt-1 && id2 <= cnt-1 ){
            merge(id1,id2);
            mergecnt++;
        }
        else{
            puts("Invalid operation !");
        }
    }
    else{
        printf("You get only one chance!\n");
    }
    return 0; 
}
 
int selectenemy() {

    printf("Battle \n");
    printf("Enter enemy id : ");
    int idx;
    scanf("%d",&idx);
    battle(idx);
    return 0; 
}

void end(char *buf){
    printf("See you on the other side ...\n");
}

void menu(){
    puts("============== MENU ==============");
    puts("| 1. Add Enemy                   |");
    puts("| 2. Battle                      |");
    puts("| 3. Merge                       |");
    puts("| 4. Enter any other key to flee |");
    puts("==================================");
    printf(">> ");
}

int main(){

    init();
    p = (Player*)malloc(sizeof(Player));
    p->name = (char *)malloc(0x40);
    printf("Who dares to enter these hallowed halls!! : ");
    get_str(p->name, 0x40);
    p->atk = 15;
    p->hp  = 100;

    master * chunk =(master*)malloc(0x50);
    chunk->fnptr = end; 

    puts("    _                  _               _     _   _                          \r\n   / \\    _ __    ___ (_)  ___  _ __  | |_  | | | |  ___   _   _  ___   ___ \r\n  / _ \\  | '_ \\  / __|| | / _ \\| '_ \\ | __| | |_| | / _ \\ | | | |/ __| / _ \\\r\n / ___ \\ | | | || (__ | ||  __/| | | || |_  |  _  || (_) || |_| |\\__ \\|  __/\r\n/_/   \\_\\|_| |_| \\___||_| \\___||_| |_| \\__| |_| |_| \\___/  \\__,_||___/ \\___|\r\n                                                                            \r\n");

    while(1){
        menu();
        int choice;

        scanf("%d",&choice);

        switch(choice){
            case 1:
                playeralloc();
                break;
            
            case 2:
                selectenemy();
                break;

            case 3:
            
                selectmerge();
                break;
                
            default:
                (chunk->fnptr)(chunk->arg);
                exit(1);

        }
    }
    return 0;
}

