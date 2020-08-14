#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


char name[16] = {'\x00'};
unsigned char key[16] = {'\x00'};
unsigned char IV[16] = {'\x00'};

int count=0;

struct spells
{
  int vid;
  int len;
  //char *pt;
  char *ct;
}vault[9];

void encrypt(char *pt, char *ct)
{
 
 AES_KEY enc_key;
 unsigned char local_vector[16] = {'\x00'};
 memcpy(local_vector,IV,AES_BLOCK_SIZE);
 
 AES_set_encrypt_key(key, sizeof(key)*8, &enc_key);
 AES_cbc_encrypt(pt,ct,strlen(pt), &enc_key, local_vector, AES_ENCRYPT);
 return;
}

void decrypt(char *pt, char *ct)
{
 
 fflush(stdin);
 char iv[32] = {'\x00'};
 printf("\nEnter IV:");
 scanf("%17c",iv);
 iv[16]='\x00';
 AES_KEY dec_key;
 unsigned char local_vector[16] = {'\x00'};
 memcpy(local_vector,iv,AES_BLOCK_SIZE);
 AES_set_decrypt_key(key, sizeof(key)*8, &dec_key);
 AES_cbc_encrypt(ct,pt,strlen(ct), &dec_key, local_vector, AES_DECRYPT);
 
 return;

}

int hextostring(char *data,char *ct,int data_len)
{
  int i=0,j=0;

  if(data_len % 2 == 1)
  {
    //odd-length string... adding 0
    if(sscanf(&(data[0]), "%1hhx",&(ct[0]))!=1)
    {
      printf("\nSome error when reading :(");
      return -1;
    }

    i = j =1;
  }

  for(; i<data_len; j++,i+=2)
  {
    if(sscanf(&(data[i]), "%2hhx", &(ct[j])) != 1)
    {
      printf("\nSome error when reading :(");
      return -1;
    }
  }
  return 0;
}

void print_data(char *data, int len)
{
	for(int i=0; i<len;i++)
	{
		printf("%02x",(unsigned char)data[i]);
		//printf("%c-->%d",data[i],i);
	}

	printf("\n");
	return;
}

void generator()
{
	FILE * fp = fopen("/dev/urandom","rb");
	FILE *fp1 = fopen("key.txt","rb");
	if(fp < 0)
	{
		printf("Error in reading key!");
		exit(1);
	}

	else
	{
		fread(&key,0x10,1,fp1);
		fread(&IV,0x10,1,fp);
		printf("IV:");
		print_data(IV,16);
	}

	return;
}

void add_padding(char *data)
{
  int l;
  int len = strlen(data);
  if(len > 0)
  {

    l = 16-(len % 16);
    for(int i=0; i<l; ++i)
    {
      *(data + (i+(len))) = l;
    }
  }
  return;
}

void remove_padding(char *data)
{

  int end = (unsigned int)(data[strlen(data)-1]);
  int data_len = strlen(data)-end;
  //printf("%d",end);
  if(end<=16)
  {
    printf("padding len %d\n", end);
    for(int i=0; i<end;i++)
      *(data + (i+data_len)) = '\x00';
    return;
  }

  else
  {
  	printf("Whoops\n");
  	exit(0);
  }
}

void read_data(char *data, int data_len)
{
  
  fgets(data,data_len+1,stdin);
  data[strlen(data)-1] = '\x00'; 
  return;
}

int menu()
{
  int opt;
  printf("Behold young mortal! Welcome to Hade's land\n");
  printf("1. Conceal ya spell\n");
  printf("2. Change code\n");
  printf("3. Recover ya magic\n");
  printf("4. Quit ya quest\n");
  scanf("%d",&opt);
  getchar();
  //fflush(stdin);
  return opt;

}

void conceal(int id)
{
  if(count<=8 && vault[id].vid != id+1)
  {
    unsigned int c;
    //printf("%d-->%d\n",vault[id].vid,id+1);
    char data[1024]={'\x00'};
    int len;
    vault[id].vid = id+1;
    //print_data(data,strlen(data));
    printf("Enter the size:\n");
    scanf("%d",&c);
    getchar();
    if(c >= 0 && c <= 0x70)
    {
      printf("Please enter your plaintext:");
      read_data(data,c+1); //changing it here to limit the size of chunks to fastbins
      vault[id].ct = (char *)malloc(c+0x10);
      vault[id].len = strlen(data);
      //if(strlen(data)%16!=0 && id!=9)
      add_padding(data);
      //print_data(data,strlen(data));
      encrypt(data,vault[id].ct);
      printf("\nEnchanted spell concealed!\n");
      print_data(vault[id].ct,strlen(vault[id].ct));
      printf("\n");

      count+=1;
    }

    else
    {
      printf("A mistake young one ;)\n");
    }

  }

  else
  {
    printf("Someone already filled up all vaults.\n");
  }

  return;

}

void change_name()
{
	
	char pt[32]={'\x00'};
	char value[40]={'\x00'};
	char imdt [40]={'\x00'};
    
	printf("Enter encrypted name:");
	read_data(value,32);
	hextostring(value,imdt,32);
	decrypt(pt,imdt);
	
	remove_padding(pt);
	strncpy(name,pt,16);
	printf("Your new name:");
	printf(name);

	return;
	
}

void remove_trace(unsigned int id)
{
  if(count<=8 )//&& vault[id].vid == id+1)
  {
    printf("Emptying your vault...");
    free(vault[id].ct);
    vault[id].vid = 0;
  }

  else
  {
    printf("A mistake young one ;)\n");
  }

  return;
}

void end_quest()
{
  char data[128] = {'\x00'};
  printf("\n... ending ya quest here?\n");
  read(0,data,120);
  // giving a fortify enabled so that attacker dusn do a format string
  printf("%s",data);
  exit(0);
}

int main()
{
	
  setvbuf(stdout,NULL,2,0);
  setvbuf(stdin,NULL,2,0);	
  generator();

  unsigned int opt;
  unsigned int id;

  char pt[20] = {'\x00'};
  char ct[20] = {'\x00'};

  printf("Behold young mortal! Welcome to Hade's land\n");
  printf("Enter 3 letter-code :");
  scanf("%4c",name);
  name[3] = '\x00';
  strcpy(pt,name);
  add_padding(pt);

  printf("Encrypted code : ");
  encrypt(pt,ct);
  print_data(ct,16);

  while(1)
  {
    printf("\nEnter your vault ID:");
    scanf("%d",&id);
    //improving id search function? TBA

    if(id>0 && id<=9)
    {
      opt = menu();
      switch(opt)
      {
      case 1: conceal(id-1);break;
      case 2: change_name();break;
      case 3: remove_trace(id-1);break;
      case 4: end_quest();break;
      default: printf("Don't joke with me!");

      }

    }
    else
    {
      printf("Your quest has ended here.\n");
      break;
    }
    

  }


  return 0;

}

