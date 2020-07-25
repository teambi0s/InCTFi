#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NAME_LEN 0x50
#define DESC_LEN 0x100


struct note {
    char name[NAME_LEN];
    long long size;
    char *desc;
};

struct note *table[10] = {0};


int get_inp(char *buffer, int size) {
    int retval = read(0, buffer, size);
    if (retval == -1)
        exit(0);
    if ( buffer[retval-1] == '\n')
        buffer[retval-1] = '\0';
    return retval-1;
}


int get_int() {
    char buffer[32];
    get_inp(buffer, 32);
    return atoi(buffer);
}


long long get_ll() {
    char buffer[32];
    get_inp(buffer, 32);
    return atoll(buffer);
}


int insert(char* name, long long size, char *desc, int idx) {
    table[idx]->size = size;
    table[idx]->desc = desc;
    strcpy(table[idx]->name, name);
    return 0;
}


int add_note() {
    int i = 0;
    char desc[DESC_LEN] = {0};
    char name[NAME_LEN] = {0};
    char *ptr;
    long long size;
    for ( i = 0; i < 10; i++)
        if (table[i] == NULL)
            break;
    if ( i == 10)
        return 0;
    printf("ID : %d\n", i);
    printf("Enter name: ");
    fgets(name, NAME_LEN+1, stdin);
    printf("Enter desc: ");
    fgets(desc, DESC_LEN+1, stdin);
    size = strlen(desc);
    ptr = strdup(desc);
    table[i] = (struct note*) malloc(sizeof(struct note));
    insert(name, size, ptr, i);
    return i;
}


int edit_note() {
    int idx = 0;
    char desc[DESC_LEN] = {0};
    char name[NAME_LEN] = {0};
    char *ptr;
    long long size;
    printf("Enter index: ");
    idx = get_int();
    if ( idx < 0 || idx > 9 || table[idx] == NULL)
        return 0;
    printf("Enter name: ");
    fgets(name, NAME_LEN+1, stdin);
    printf("Enter size: ");
    size = get_ll();
    printf("Enter desc: ");
    if ( size <= DESC_LEN) {
        fgets(desc, DESC_LEN+1, stdin);
        ptr = strdup(desc);
    }
    else {
        ptr = malloc(size);
        fgets(ptr, size+1, stdin);
    }
    insert(name, size, ptr, idx);
    return 0;
}


int remove_note() {
    int idx;
    printf("Enter idx: ");
    idx = get_int();
    if ( idx < 0 || idx > 9 || table[idx] == NULL)
        return 0;
    free(table[idx]->desc);
    table[idx]->desc = NULL;
    free(table[idx]);
    table[idx] = NULL;
    return 0;
}


int view_note() {
    int idx;
    printf("Enter idx: ");
    idx = get_int();
    if ( idx < 0 || idx > 9 || table[idx] == NULL)
        return 0;
    printf("Note ID : %d\nName : %s\n", idx, table[idx]->name);
    printf("Size : %lld\nDescription : %s\n", table[idx]->size, table[idx]->desc);
    return 0;
}


int printmenu() {
    puts("1) Add note\n2) Edit note\n3) Remove note\n4) View note\n5) Exit");
    printf(">> ");
    return get_int();
}


int main() {
    alarm(30);
    setvbuf(stdout, NULL, _IONBF, 0);
    puts("---------------------------");
    do {
        switch(printmenu()) {
            case 1: add_note(); break;
            case 2: edit_note(); break;
            case 3: remove_note(); break;
            case 4: view_note(); break;
            case 5: exit(0);
            default: puts("Invalid"); break;
        }
    } while(1);
    return 0;
}
