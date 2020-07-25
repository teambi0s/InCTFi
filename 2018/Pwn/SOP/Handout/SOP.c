// gcc -pie -fPIE SOP.c -o SOP -fno-builtin-printf -Wl,-z,relro

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include"const.h"

struct details{
		char name[200];
	  	char *desc;
}one;

char a[val]="erhtlo,r.tbrtwop,btplgbrkmdgbkwm;nwmad;groanmdkbrm;dlrwnkmb";
char details[200];

int get_inp(char *s,int size){
	int n;
	char c;
	n=read(0,s,size);
	if(n==-1)
		exit(0);
	if(s[n-1]=='\n')
		s[--n]='\0';
	return n;
}

int initialise()
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
}


void main(){
	initialise();
	banner();
	printf("Enter your Name\n");
	get_inp(one.name,208);
	one.desc="Default Description";

	while(1){
		int ch;
		printf("Are you sure?\n");
		printf("\t\t1. VIEW\n");
		printf("\t\t2. EDIT NAME\n");
		printf("\t\t3. EDIT DESC\n");
		printf("\t\t4. SUBMIT\n");
		printf("Enter you choice\n");
		scanf("%d",&ch);

		if(ch==1){
			printf("Name: %s\n",one.name);
			printf("Desc: %s\n",one.desc);
		}


		if(ch==2){
			printf("Change Your Name\n");
			get_inp(one.name,208);
		}

		if(ch==3){
			printf("Change your description\n");
			get_inp(one.desc,250);
		}


		if(ch==4){
			printf("Your SOP has been submitted\nTHANK YOU\n");
			exit(0);
		}

	}


}
