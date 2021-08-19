
#include<stdio.h>
#include<string.h>
#include <unistd.h>
#include<stdlib.h>
char ip[30];
int v1[30];
char op[25];
char str[25]="inctf{U_Sur3_m4Te?}";
const char pic[]=" ________ \n|        |\n|  V  V  |\n|   __   |\n|  [__]  |\n|________|\n";
const char pic2[]="\n ................\n |w00ff w00ff!! |\n  '''''V'''''''' \n \n     .~````~. \n  .,/        \\,. \n (  | (0  0) |  )\n (  |  ____  |  )\n (_/|  \\__/  |\\_)\n     \\__/\\__/\n      '-..-'  \n\n";
int lost(){

	printf("%s\n",pic);
	printf("Lol , he won't come to you that easy..Try again! \n");
	exit(1);

}
void floor1(int v1[]){
	op[0]=(v1[0]^0x32%4)-31;
	op[1]=((v1[1] %2 )^v1[0])-29; 
	op[2]=(v1[1] << 0x2) ^407;
	op[3]=(v1[2]^416) ;
	op[4]=(v1[3] ^0x4d)+7;
	op[5]=(v1[5] << 0x2)-1;
	op[3]=v1[4]+116;
	op[6]=(v1[6] -6379);
	op[7]=5 +v1[7]-0x19;
	op[8]= 0x63 ^ v1[8];
	op[9]=54+(v1[10]^3)-v1[8] ;
	op[10]= (114 & 79)^v1[9];
	op[11]=51 + v1[11];
	op[11] = (v1[12]^ 179);
	op[12]= 26^(v1[13]+18);
	op[13]= 59+(v1[14]-66);
	op[14]=v1[15]-37;
	op[15] =v1[17]^ 0xe4 +1;
	op[16]=( v1[18]& 0x36)+53;
	op[14]=v1[19]^52;
	op[17]=(v1[20]^253);
	op[18]=(v1[20]>>v1[21])^28;

	 if(strcmp(op,str)==0){
		printf("%s",pic2);
		printf("\nYeey you found him !!!!\n Grab your reward!\n : inctf{%s}\n ", ip);
		exit(1);
	} 
	else 
		lost();	
}

int main(){
	
	printf("Hello there , i lost my dog pluto :(\nHelp me call him out please !!\n");
	scanf("%s",ip);
	if(strlen(ip)!=30){
		lost();
	}
    v1[0]=ip[0]-0x32+ip[1];
    v1[1]=ip[1]-0x64+ip[2];  
    v1[2]=4*ip[2];
    v1[3]=ip[3]^70;
	v1[4]=36-(ip[3]-ip[4]);
	v1[5] = ip[5]-(ip[4])^48;
	v1[6] = (ip[6] * ip[5]) + 0x63;
	v1[7] = ip[6] ^ ip[7];
	v1[8] = (ip[7] + 0x2d) ^ ip[8];
	v1[9] = (ip[9] &55)-3;
	v1[10] = 64+ip[10] - (ip[9]);
	v1[11] = ip[11] -38;
	v1[12] = ((ip[12] ^ ip[6]) * 4)+16;
	v1[13]=ip[13]^84;
	v1[5] = ip[21]-(ip[4])^48;
	v1[13] = (ip[13]-ip[14])-1;
	v1[14] = ip[15];
	v1[15] = 3+(ip[16] ^ ip [15])*2;
	v1[10]=ip[17]-ip[16]+82;
	v1[16] = (ip[19] *4);
	v1[16] = ((ip[18] ^ip[19])*6)+54;
	v1[17] = (ip[20] ^ 0x73) + (ip[21] + 0x31);
	v1[14]=ip[22];
	v1[18] = (ip[23] << 1)^(161+ip[24]);
	v1[18]=ip[23]^66;
	v1[15]=ip[26]+5;
	v1[19] = ip[25] -(ip[26]/2)-55;
	v1[20] = (ip[27] ^ ip[28])+173;
	v1[20] =(ip[27] << 2)-(ip[28]+128);
	v1[21] = (ip[29]-32);

    floor1(v1);
}
