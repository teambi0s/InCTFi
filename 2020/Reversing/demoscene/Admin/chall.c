#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

//clang -mllvm -bcf  -mllvm -sub_loop=3 -mllvm -aesSeed=B105B105B105B105B105B105B105B105 chall.c -o cryptor_obfus.exe
void wrapperputs(char* str1);
void wrapperstrcpy(char* og,char* dest);

typedef struct demo_scene_data
{
    char demeoscene[100000];
    int dembuff_size;

}*pdemo_scene_data,demo_scene_data;

void error(int x){
    switch(x){
        case 1:
            printf("Something doesn't seemt to be right\n");
            exit(1);
            break;

        case 0:
            printf("Some internal Failure has occurred\n");
            exit(255);
            break;
        default:
            printf("-------------------------\n");
    }
}

void print_welc(){
    char OutBuff[1337]; 
    strcpy(OutBuff,"Welcome to INCTF International\n");
    puts(OutBuff);
    strcpy(OutBuff,"We are in works to make a trivial file encryptor -\n");
    puts(OutBuff);
}



void encryptor(demo_scene_data rd){
    char key[] = "7h15157h3n3w8391nn1n9";
    char temp_arr[100000];
    //Here we are finding the lenght of the string passed to it
    int len = rd.dembuff_size;
    char* tmp = rd.demeoscene;
    char temp;
    char* out = (char*)(malloc(sizeof(char)* len));
    int i;
    FILE *fptr;

    for(i = 0; i < len; i++){
        temp = tmp[i] ^ key[i % 21];
        temp_arr[i] = temp;
    }
    memcpy(out,temp_arr,rd.dembuff_size);
    fptr = fopen("wut", "w");
    for(i = 0; i < len; i++){
        putc(temp_arr[i], fptr);
    }
    fclose(fptr);
}

void read_bin(demo_scene_data rd)
{
    //This is the function that is responsible for reading encrypted demoscene binary.
    HANDLE hFile;
    DWORD dwBytesRead;
    
    hFile = CreateFile("demo.exe",               
                       GENERIC_READ,         
                       FILE_SHARE_READ,       
                       NULL,                  
                       OPEN_EXISTING,         
                       FILE_ATTRIBUTE_NORMAL, 
                       NULL);
    
    if(hFile == INVALID_HANDLE_VALUE) 
    { 
        error(1);
    }    
   
   ReadFile(hFile, rd.demeoscene, rd.dembuff_size, &dwBytesRead, NULL);
   rd.dembuff_size = dwBytesRead;
   encryptor(rd);
   CloseHandle(hFile);
}

int main(){
    demo_scene_data d;
    d.dembuff_size = 44544;

    print_welc();
    read_bin(d);
}