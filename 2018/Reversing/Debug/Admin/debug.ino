#include<Keypad.h>
#include<Key.h>
#include"custom.h"
const byte nR=4;
const byte nC=4;

char keymap[nR][nC]={{'1','2','3','A'},
                    {'4','5','6','B'},
                    {'7','8','9','C'},
                    {'*','0','#','D'}};

byte rowPins[nR]={10,9,8,7};
byte colPins[nC]={6,5,4,3};

int in[4]={7,3,3,1};
int inputar[4];
int input_intg,k=0;

char fl[19];
char flg[19];

Keypad Key = Keypad(makeKeymap(keymap),rowPins,colPins,nR,nC); 

void secret()
{
  int n=0;
  for(n=0;n<4;)
  {
    char input = Key.getKey();
    if(input)
  {
      Serial.print(input);
      if(input!=in[n])
    {
        Serial.print("Pin mismatch");
        delay(1200);
        loop();
    }
    inputar[n]=input;
    n++;
   }
  for (int i = 0; i < 4; i++)
    input_intg = 10 * input_intg + inputar[i];
  Serial.print(flg);  
  }
}

void gen()
{
    fl[0]=S[8];
    fl[1]=S[13];
    fl[2]=S[2];
    fl[3]=S[19];
    fl[4]=S[5];
    fl[5]=S[69];
    fl[6]=S[56];
    fl[7]=S[47];
    fl[8]=S[17];
    fl[9]=S[75];
    fl[10]=S[63];
    fl[11]=S[18];
    fl[12]=S[39];
    fl[13]=S[19];
    fl[14]=S[75];
    fl[15]=S[27];
    fl[16]=S[56];
    fl[17]=S[29];
    fl[18]=S[70];
   
   for(int i=0;i<19;i++)
  {
        flg[i]=fl[i]^input_intg;
  }
}

void setup()
{
    Serial.begin(9600);
    gen();
}
void loop()
{
    secret();
}
