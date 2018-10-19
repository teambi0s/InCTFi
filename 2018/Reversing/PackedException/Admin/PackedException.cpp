/*flag: Inctf{T#@n0$_K!||$_w!t#0uT_@nY_3xc3pT!0n}
input:T#@n0$_K!|wtu3xcpY
input:T#@ n0$ _K! |wt u3x cpY

" */

#include<string.h>
#include<iostream>
#include<stdio.h>
using namespace std;
void Than0sWins(char *arr)
{
	char galf[35];
	for(int i = 0; i<10; i++)
	{

		galf[i] = *(arr + i);
	}

	galf[10] = *(arr + 9);
	galf[11] = *(arr + 5);
	galf[12] = *(arr + 6);
	galf[13] = *(arr + 10);
	galf[14] = *(arr + 8);
	galf[15] = *(arr + 11);
	galf[16] = *(arr + 1);
	galf[17] = *(arr + 4);
	galf[18] = *(arr + 12);
	galf[19] = *(arr + 0);
	galf[20] = *(arr + 6);
	galf[21] = *(arr + 2);
	galf[22] = *(arr + 3);
	galf[23] = *(arr + 17);
	galf[24] = *(arr + 6);
	galf[25] = *(arr + 13);
	galf[26] = *(arr + 14);
	galf[27] = *(arr + 15);
	galf[28] = *(arr + 13);
	galf[29] = *(arr + 16);
	galf[30] = *(arr + 0);
	galf[31] = *(arr + 8);
	galf[32] = *(arr + 4);
	galf[33] = *(arr + 3);

	cout<<"\n\nHere is your Flag: inctf{";
	for(int i = 0; i<34; i++)
		cout<<galf[i];
	cout<<"}\n\n\n";
}



void IamGrooot(char *arr, int *ret)//1st
{
	char out[4] = "T#@";
	char temp[4];
	int i = 0;
	for(i = 0; i<3; i++)
	{
		temp[i] = *(arr+i);
	}
	*ret = strncmp(temp,out,3);
	if(*ret != 0)
	{
		*ret = 0;
		throw "You Failed to find the Final Infinity Stone.";
	}
	else
	{
		*ret = 1;
		throw "You Found the First Infinity Stone.";
	}
}


int TonyStark(char *arr, int*ret)
{//_K!
	int flag = 1;
	char out[4] = "!K_";
	char t[4];
  char ch;
  for(int i = 0; i<3; i++)
	{
		t[i] = *(arr + i);
  }
  ch = t[0];
  t[0] = *(arr + 2);
  t[2] = ch;
	*ret = strncmp(t,out, 3);
  if(*ret == 0)
  {
		*ret = 1;
    throw "You Found the Second Infinity Stone.";
  }
  else
  {
		*ret = 0;
    throw "You Failed to find the Second Infinity Stone.";
  }
}

int WarInTitan(char *arr, int*ret)
{//n0$

	int flag = 1;
	int i = 0;
	int temp = 0;
	char array[4];
	for(i = 0; i<3; i++)
	{
		array[i] = *(arr + i);
	}
	i = 0;
	while(i < 3)
	{
		temp = 0x12345;
		if(i <= 1)
		{
			if(i > 0)
			{
				int c = (int)(array[i]);
				c = c ^ temp;
				if (c != 74613)
				{
					flag = 0;
				}
			}
			else
			{
				int c = (int) array[i];
				c = c ^ temp;
				if (c != 74539)
				{
					flag = 0;
				}
			}

		}
		else
		{
			int c = (int) array[i];
			c = c ^ temp;
			if (c != 74593)
			{
				flag = 0;
			}
		}
	i = i+1;
	}

	*ret = flag;
	if(*ret == 0)
	{
		throw "You Failed to find the Third Infinity Stone.";
	}

  else
	{

		throw "You Found the Third Infinity Stone.";
	}
}


void WakandaForever(char *arr, int*ret)
{
//cpY
	int flag;
	char str[] = "gt]";
	for(int i = 0; i<3; i++)
	{
		if((int(*(arr + i)) ^ 4) != int(str[i]))
		{
			flag = 1;
		}
	}
	*ret = flag;

	if(*ret == 1)
	{
		throw "You Failed to find the Forth Infinity Stone.";
	}
	else
	{
		*ret = 0;
		throw "You Found the Fourth Infinity Stone.";
	}
}



void VisionDies(char *arr, int*ret)
{
	//u3x
	char out[] = "w5z";
	char temp[3];
	int i = 0;
	int junk = 0x123456;
	junk = junk >> 3;
	if(junk != 0)
	{
		junk = junk ^ 1210;
		if(junk == 0)
		{
			throw "Error";
		}
		else
		{
			junk = junk >> 5;
			if(junk > 4000)//4625
			{
				junk = junk - 4100;

				if(junk > 600)
				{
					throw "You did Something Wrong.";
				}

				else
				{
					junk = junk / 25;

					if(junk > 25)
					{
						throw "You are not supposed to patch this.";
					}
					else
					{
						junk = junk % 19;
						if(junk < 1 || junk >= 5)
						{
							throw "Avengers Won";
						}
						else
						{
							for(int i = 0; i<3; i++)
							{
								temp[i] = (*(arr + i) + junk);

							}
							junk = strncmp(temp, out,3);
							if(junk == 0)
							{
								*ret = 1;
								throw "You Found the Fifth Infinity Stone.";
							}
							else
							{
								*ret = 0;
								throw "You Failed to find the Fifth Infinity Stone.";
							}
						}
					}
				}
			}
			else
			{
				throw "error";
			}
		}
	}
	else
	{
		throw "Error";
	}
}



int TheFinalBattle(char *arr, int*ret)
{
	char out[] = "elm";
	//|wT
	char temp[4];
	for(int i = 0; i<3; i++)
	{
		temp[i] = ((*(arr+i) ^ 30) + 3);
	}
	int junk = strncmp(temp, out,3);
	if(junk != 0)
	{
		*ret = 0;
		throw "You Failed to find the Final Infinity Stone.";
	}

	else
	{
		*ret = 1;
		throw "You Found the Sixth Infinity Stone.";
	}
}


int etaluclac(char *arr, int *ret, int n)
{
	int r;
	if(n == 1)
	{
		cout<<"\n\nYou have to help THANOS to get all the Six Infinity Stones.\n";
		cout<<"\nRemember each Infinity Stone will be difficult to find than the previous one.\n\n";
	try{
			IamGrooot(arr, ret);
			}catch(const char * mssg){
				cout<<"\n"<<mssg<<"\n";
				}
		if(*ret == 1)
		{
			return 	1;
		}
		else
		{
			return 0;
		}
	}

	if(n == 2)
	{
	try{
			TonyStark((arr + 6), ret);
	}catch(const char * mssg){
		cout<<"\n"<<mssg<<"\n";
		if(*ret == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	}

	if(n == 3)
	{
	try{
			WarInTitan((arr + 3), ret);
	}catch(const char * mssg){
		cout<<"\n"<<mssg<<"\n";
		if(*ret == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
	if(n == 4)
	{
		try{
			WakandaForever((arr + 15), ret);
				}catch(const char * mssg){
				cout<<"\n"<<mssg<<"\n";
		if(*ret == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}

		}
	}

	if(n == 5)
	{
		try{
			VisionDies((arr + 12), ret);
				}catch(const char * mssg){
		cout<<"\n"<<mssg<<"\n";
		if(*ret == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
		}
	}

	if(n == 6)
	{
	try{
			TheFinalBattle((arr + 9), ret);
	}catch(const char * mssg){
		cout<<"\n"<<mssg<<"\n";
		if(*ret == 1)
		{
			Than0sWins(arr);
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

	//Than0sWins(arr);

}

void htgnel(char *arr1, int *ret1)//checks if the length == 18
{
	int i = 0;

	while(*(arr1 + i) != '\0')
	{
		i++;
	}

	if(i > 0x1A || i < 0xA)
	{
		*ret1 = 0;
	}
	else if(((i << 10 ) % 1000) != 0x1b0)
	{
		*ret1 = 0;
	}

	else
	{
		*ret1 = 1;
	}

	if(*ret1 == 0)
	{
		throw "Oops You Did'nt Think Properly..";
	}

	else
	{
		throw "Correct!\n";
	}
}


int main()
{
	char input[30];
	cout<<"\n\nInput: ";
	cin.getline(input,30);
	char *point = input;
	int a = 0;
	int r = 1;
	int *ret1 = &a;
	try{

		htgnel(point, ret1);

	}catch(const char *msg){
		cout<<"\n"<<msg;
		if(a == 1)
		{
			int i = 1;
			while(i <= 6)
			{
				r = etaluclac(point,ret1,i);
				if(r == 0)
				{
					cout<<"\n\nYou have my respect. I hope the people will remember your Legacy..\n\n";
					cout<<"You Lose..\n\n";
					break;
				}
				else
					i = i+1;
			}
		}
		else
		{
			cout<<"\nYou Lose.";
		}
	}
	return 0;
}
