#include<stdio.h>
#include<windows.h>
#include<strings.h>

#define fool1 "#f}wLG{ L} "
#define lepc0 "}[2waHmrgxj"
#define flag "X1t^Uintfiu^Xnt^B`o^Rnmwd^Uihr^Edbnx>>>!;Q"
#define mock "Usx^@^Ehggdsdou^@qqsn`bi^;Q"
#define fool2 "amppgav"
#define ring "#f}wLG{ L} "
#define Flag "inctf{}"
#define decoy "WnvkocvgFgam{KqJgpg"

//Wrong Input Messages
void func32()
{
	printf("\n\nwrong Input");
}

void func31()
{
	printf("\n\nIt seems you made a tiny mistake.");
	printf("\nBetter Luck NextTime");
}


void func34()
{
  int i = 0;
  char j = 'a';
	char m[10];

	for(i = 0; i< strlen(Flag); i++)
	{
		m[i] = Flag[i];
	}

  printf("\n");
	for(i = 0; i<strlen(flag); i++)
  {
    j = (flag[i] ^ 1);
    printf("%c", j);
  }
    printf("\n\n");
  for(i = 0; i<strlen(mock); i++)
  {
    j = (mock[i] ^ 1);
    printf("%c", j);
  }
  printf("\n");
}


//Correct Flag Function

void func33(char *p)
{
	int i = 0;
	int k = 0;
	printf("\n\n");
	for(i = 0; i < strlen(fool2); i++)
	{
		k = fool2[i] ^ 2;
		printf("%c", k);
	}
	printf(": ");
	for(i = 0; i<44; i++)
	{
		printf("%c", *(p + i));
	}
	printf("\n\n");
}


//Debugger Checks
int IsDbg()
{
	if (IsDebuggerPresent())
	//printf("debugger found");
        return 13;
	else
        return 14;
}


int DebugDecoy11(int *k, int *l, int *m)
{
		int r = IsDbg();
		int p = 11;
		if(r > 10)
		{
			p = *k + *l + *m + r;
			p = p - 0x24f6;
			p = p % 990;
			p = p + 4;
			return p;
		}
		else
		{
			p = *k + *l + *m + r;
			p = p - 0x24f6;
			p = p % 990;
			p = p + 4;
			return p;
		}
}


int DebugDecoy1()
{
	int a = 0xbeef, b = 0xdead, c = 0xdec;
	int *a1;
	int *b1;
	int *c1;

	a1 = &a;
	b1 = &b;
	c1 = &c;

	int ret = DebugDecoy11(a1,b1,c1);

	if(a > 10000)
	{
		if(b > 50000)
		{
			if(c > 500000)
			{
				ret = ret + 4;
			}
			else
			{
				ret = ret - 10;
			}
		}
		else
		{
			if(c > 500000)
			{
				ret = ret - 12;
			}
			else
			{
				ret = ret + 3;
			}
		}

	}
	else
	{
		if(b > 50000)
		{
			if(c > 500000)
			{
				ret = ret - 6;
			}
			else
			{
				ret = ret - 7;
			}

		}
		else
		{
			if(c > 500000)
			{
				ret = ret - 5;
			}
			else
			{
				ret = ret - 5;
			}
		}
	}
	return ret;

}



//DebugCheck2
int ReDbgChe()
{

	if (IsDebuggerPresent())
        return 2;
	else
        return 0;
}

//Calculate length

int calcLength(char inp[])
{
  int a = 0;
  return strlen(inp);
}



//First Input Check

int func1(char *c) //correct check
{
  char d[12];
  int i = 0,j=0;
  char joker[12];
  int O=0;
  int V12=0;

  for (i=0;i<11;i++)
  {
    d[i]=(*(c+i)^8+3);
  }

  for (i=0;i<11;i++)
  {
        d[i]=d[i]^19;
  }

  for (j=0;j<11;j++)
  {
      joker[j]=((ring[j])^11);
  }

  joker[j]=0;

  while(O<11)
  {
    if(d[O]==joker[O])
    {
      V12++;
      O++;
    }
    else
    {
      V12=0;
     O++;
    }
  }
  return V12;
}

//Check1 Decoy
int func2(char *c)
{
    char d[12];
    int j=0,i= 0;
    char joker[12];
    int O=0;
    int V12=0;


    for (i=0;i<11;i++)
    {
      d[i]=(*(c+i)^7+3);
		}

    for (i=0;i<11;i++)
    {
      d[i]=d[i]^9;
    }



    for (j=0;j<11;j++)
    {
      joker[j]=((ring[j])^11);
    }

    joker[j]=0;

    while(O<11)
    {
    	if(d[O]==joker[O])
      {
        V12++;
        O++;
      }
    	else
    	{
        V12=0;
				O++;
    	}
    }
return V12;

}


//level2 check

//Correct Check
int func3(char *b)
{
	char art[12];
	int counter = 0, k = 0, v2 = 0, v3 = 0, v3n0m = 0;

	while ((counter>=0)&&(counter <5))
  {
    art[k+6]=(*(b+counter)+((34%8300)>>3));
    art[k]=(*(b+counter+5)+((11%8300)>>2));
    counter++;
    k++;
  }
  art[5]=*(b+10)+2;

	while(v2<1)
  {
    for (v3=0;v3<11;v3++)
    {
      if(lepc0[v3]==*(art+((v2+v3)%11)))
      {
        v3n0m++;
      }
    }
    v2++;
  }
	return v3n0m;
}

//Check2 Decoys
int func4(char *b)
{
	char art[12];

	int counter = 0, k = 0, v2 = 0, v3 = 0, v3n0m = 0;

	while ((counter>=0)&&(counter <5))
	{
  	art[k+6]=(*(b+counter)+((34%8300)>>1));
  	art[k]=(*(b+counter+5)+((11%8300)>>5));
  	counter++;
  	k++;
	}
  art[5]=*(b+10)+2;

	while(v2<1)
  {
    for (v3=0;v3<11;v3++)
    {
      if(lepc0[v3]==*(art+((v2+v3)%11)))
      {
        v3n0m++;
      }

    }
    v2++;
  }

	return v3n0m;
}




int func5(char *b)
{
	char art[12];
	int counter = 0, k = 0, v2 = 0, v3 = 0, v3n0m = 0;

	while ((counter>=0)&&(counter <5))
  {
  	art[k+6]=(*(b+counter)+((34%8300)>>1));
    art[k]=(*(b+counter+5)+((11%8300)>>2));
    counter++;
    k++;
  }
  art[5]=*(b+10)+4;

	while(v2<1)
  {
    for (v3=0;v3<11;v3++)
    {
      if(lepc0[v3]==*(art+((v2+v3)%11)))
      {
      	v3n0m++;
      }
    }
    v2++;
  }

	return v3n0m;
}


int func6(char *b)
{
	char art[12];
	int counter = 0, k = 0, v2 = 0, v3 = 0, v3n0m = 0;

	while ((counter>=0)&&(counter <5))
  {
    art[k+6]=(*(b+counter)+((34%8300)>>3));
    art[k]=(*(b+counter+5)+((11%8300)>>5));
    counter++;
    k++;
  }
  art[5]=*(b+10)+2;

	while(v2<1)
  {
    for (v3=0;v3<11;v3++)
    {
      if(lepc0[v3]==*(art+((v2+v3)%11)))
      {
        v3n0m++;
      }
    }
    v2++;
  }

	return v3n0m;
}


//level3
//correct Check
int func7(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] = {0x7b,0x60,0x49,0x35,0x7a,0x25,0x75,0x35,0x64,0x4c,0x7e};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }
    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);

    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

//Check3 Decoys
int func8(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x62, 0x65, 0x6d, 0x61, 0x6c, 0x69, 0x63, 0x69, 0x6f, 0x75, 0x73};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }
    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

int func9(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x63, 0x66, 0x67, 0x61, 0x6d, 0x70, 0x63, 0x69, 0x6f, 0x74, 0x73};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }

    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

int func10(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x68, 0x70, 0x6e, 0x65, 0x6c, 0x69, 0x63, 0x69, 0x70, 0x75, 0x72};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }

    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

int func11(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x34, 0x39, 0x6d, 0x64, 0x6f, 0x69, 0x63, 0x68, 0x6f, 0x70, 0x73};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }

    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

int func12(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x63, 0x66, 0x67, 0x62, 0x6d, 0x6a, 0x64, 0x6a, 0x70, 0x76, 0x74};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }

    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

int func13(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x69, 0x37, 0x30, 0x61, 0x6f, 0x68, 0x62, 0x68, 0x70, 0x74, 0x73};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }
    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}

int func14(char *c)
{
    int y = 1;
    int i = 0;
    char a[11] ={0x62, 0x65, 0x6e, 0x62, 0x70, 0x63, 0x62, 0x70, 0x6e, 0x76, 0x75};
    char temp[11];
    for(i=0;i<11;i++)
    {
        temp[i] = *(c + i);
    }
    for(i=0;i<11;i++)
    {
        temp[i] = temp[i] + y;
    }
    int b;
    b = strncmp(a, temp, 11);
    if(b == 0)
    {
      return 11;
    }
    else
    {
      return 0;
    }
}


// Level 4 Check
//Correct Check
int func15(char *p)
{
    int y = 1, counter = 0, int i = 0;
    int a[12] = {110, 93, 57, 85, 102, 57, 112, 30, 65, 21, 125};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);

		}
		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];

			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

//Decoys
int func16(char *p)
{
    int y = 5, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x74, 32, 0x50};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}



int func17(char *p)
{
    int y = 10, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x74, 32, 0x30};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func18(char *p)
{
    int y = 8, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x64, 0x53, 0x0c, 0x45, 0x2b, 0x74, 32, 0x31};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func19(char *p)
{
    int y = 2, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0a, 0x45, 0x2b, 0x74, 32, 0x32};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}


int func20(char *p)
{
    int y = 7, counter = 0, int i = 0;
    int a[12] = {0x5c, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x56, 0x33, 0x30};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}



int func21(char *p)
{
    int y = 5, counter = 0, int i = 0;
    int a[12] = {0x5c, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2c, 0x74, 32, 0x40};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);

		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

		return counter;
}

int func22(char *p)
{
    int y = 1, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x66, 32, 0x66};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

		return counter;
}

int func23(char *p)
{
    int y = 3, counter = 0, int i = 0;
    int a[12] = {0x5c, 0x68, 0x0c, 0x61, 0x53, 0x0c, 0x45, 0x2b, 0x75, 30, 0x49};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func24(char *p)
{
    int y = 4, counter = 0, int i = 0;
    int a[12] = {0x5c, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x74, 32, 0x6f};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}



int func25(char *p)
{
    int y = 5, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x74, 32, 0x49};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);

		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func26(char *p)
{
    int y = 10, counter = 0, int i = 0;
    int a[12] = {0x5d, 0x69, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x2b, 0x74, 33, 0x49};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func27(char *p)
{
    int y = 6, counter = 0, int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x45, 0x25, 0x78, 38, 0x49};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);

		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func28(char *p)
{
    int y = 8, counter = 0;
		int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x4e, 0x2f, 0x7f, 32, 0x48};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func29(char *p)
{
    int y = 4, counter = 0;
		int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0d, 0x44, 0x2f, 0x75, 37, 0x44};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);
		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}

int func30(char *p)
{
    int y = 3, counter = 0;
		int i = 0;
    int a[12] = {0x5b, 0x68, 0x0c, 0x60, 0x53, 0x0c, 0x42, 0x2b, 0x74, 34, 0x46};
		int x[11];
		for(i = 0; i<11; i++)
		{
			x[i] = *(p + i);

		}

		for(i = 10; i>=0; i--)
		{
			x[i] = x[i] ^ y;
			y = x[i];
			if(x[i] == a[i])
			{
				counter = counter + 1;
			}
		}

    return counter;
}


//Main

int main()
{
  char input[46];
  int d1 = 1, d2 = 1;
  int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
  int length;
  char *p;
  d1 = DebugDecoy1();

  if(d1 != 4) //Debugger check Fails
	{
    printf("\nInput: ");
    fgets(input, 45, stdin);
    p = &input[0];
		length = calcLength(input);
    if(length > 22)
    {
			r1 = func2(p + 11);
      if(r1 != 11)
      {
				r2 = func5(p);
				if(r2 != 11)
				{
					d2 = ReDbgChe();//Second Debugger check
					if(d2 == 0)
					{
						if(length == 44)
						{
							r3 = func11(p+33);
							if(r3 == 11)
							{
								r4 = func17(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func16(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
            }
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func12(p+33);
							if(r3 == 11)
							{
								r4 = func17(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func18(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
				else
				{
					d2 = ReDbgChe();
					if(d2 == 0)
					{
						if(length == 44)
						{
							r3 = func13(p+33);
							if(r3 == 11)
							{
								r4 = func19(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func20(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func14(p+33);
							if(r3 == 11)
							{
								r4 = func22(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func21(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
			}
			else
			{
				//Correct Second Check
				r2 = func6(p);
				if(r2 != 11)
				{
					d2 = ReDbgChe();//Second Debugger check
					if(d2 == 0)
					{
						if(length == 44)
						{
							r3 = func8(p+33);
							if(r3 == 11)
							{
								r4 = func24(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func23(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func9(p+33);
							if(r3 == 11)
							{
								r4 = func25(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func26(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
				else
				{
					d2 = ReDbgChe();
					if(d2 == 0)
					{
						if(length == 44)//correct
						{
							r3 = func10(p+33);
							if(r3 == 11)
							{
								r4 = func27(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func28(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func8(p+33);
							if(r3 == 11)
							{
								r4 = func29(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func30(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
			}
    }
		else
    {
      func32();
    }
	}
  else
  {
    printf("\nInput: ");
    fgets(input, 45, stdin);
    p = &input[0];
    int i = 0;
    length = calcLength(input);
    if(length > 22)
    {
			r1 = func1(p+ 11);
			if(r1 == 11)
      {
				r2 = func3(p);
				if(r2 != 11)
				{
					d2 = ReDbgChe();
					if(d2 == 0)
					{
						if(length == 44)
						{
							r3 = func11(p+33);
							if(r3 != 11)
							{
								r4 = func29(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func30(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func12(p+33);
							if(r3 == 11)
							{
								r4 = func27(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func28(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
				else
				{
					d2 = ReDbgChe();
					if(d2 == 0)
					{
					  length = calcLength(input);
						if(length == 44)
						{
							r3 = func7(p+33);
							if(r3 == 11)
              {
								r4 = func15(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func33(p);
								}
							}
							else
							{
								r4 = func2(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func14(p+33);
							if(r3 == 11)
							{
								r4 = func23(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func24(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
			}
			else
			{
				r2 = func3(p);
				if(r2 != 11)
				{
					d2 = ReDbgChe();//Second Debugger check
					if(d2 == 0)
					{
						if(length == 44)
						{
							r3 = func9(p+33);
							if(r3 == 11)
							{
								r4 = func21(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func22(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func10(p+33);
							if(r3 == 11)
							{
								r4 = func19(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func20(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
				else
				{
					d2 = ReDbgChe();
					if(d2 == 0)
					{
						if(length == 44)// this is the correct path
						{
							r3 = func13(p+33);
							if(r3 == 11)
							{
								r4 = func25(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func16(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
					else
					{
						if(length == 44)
						{
							r3 = func8(p+33);
							if(r3 == 11)
							{
								r4 = func17(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
							else
							{
								r4 = func18(p + 22);
								if(r4 != 11)
								{
									func31();
								}
								else
								{
									func34();
								}
							}
						}
						else
						{
							func32();
						}
					}
				}
			}
    }
    else
    {
      func32();
    }
	}

	return 0;
}
