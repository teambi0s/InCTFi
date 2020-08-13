import sys
import fileinput
import random
import subprocess
from time import sleep
import hashlib

from Crypto.Cipher import AES


template='''
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <openssl/sha.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

int xor1[] = %s ;
int xor2[] = %s ;
long long int bin[] = %s ;

unsigned char *checksumgen(unsigned char* string, char outputBuffer[65], unsigned char hash[SHA256_DIGEST_LENGTH]){
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, string, strlen(string));
	SHA256_Final(hash, &sha256);
}
int check1(char input[14]){
        if((input[0]^input[4]^input[2]) == xor1[0])
    {

      if((input[2]^input[4]^input[6]) == xor1[1])
      {

        if((input[4]^input[6]^input[8]) == xor1[2])
        {

          if((input[6]^input[8]^input[10]) == xor1[3])
          {

            if((input[8]^input[10]^input[12]) == xor1[4])
            {

              if((input[10]^input[12]^input[1]) == xor1[5])
              {

                if((input[12]^input[1]^input[3]) == xor1[6])
                  {

                    if((input[1]^input[3]^input[5]) == xor1[7])
                    {

                      if((input[3]^input[5]^input[7]) == xor1[8])
                        {

                          if((input[5]^input[7]^input[9]) == xor1[9])
                          {

                            if((input[7]^input[9]^input[11]) == xor1[10])
                            {

                              if((input[9]^input[11]^input[13]) == xor1[11])
                              {

                                if((input[11]^input[13]^input[0]) == xor1[12])
                                {
                                  if((input[13]^input[0]^input[2]) == xor1[13])
                                  {
					return 1;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
  else
  {
  return 0;
  }
}

int check2(char input[14]){
if((input[0]^input[1]^input[2]) == xor2[0])
    {

      if((input[1]^input[2]^input[3]) == xor2[1])
      {

        if((input[2]^input[3]^input[4]) == xor2[2])
        {

          if((input[3]^input[4]^input[5]) == xor2[3])
          {

            if((input[4]^input[5]^input[6]) == xor2[4])
            {

              if((input[5]^input[6]^input[7]) == xor2[5])
              {

                if((input[6]^input[7]^input[8]) == xor2[6])
                  {

                    if((input[7]^input[8]^input[9]) == xor2[7])
                    {

                      if((input[8]^input[9]^input[10]) == xor2[8])
                        {

                          if((input[9]^input[10]^input[11]) == xor2[9])
                          {

                            if((input[10]^input[11]^input[12]) == xor2[10])
                            {

                              if((input[11]^input[12]^input[13]) == xor2[11])
                              {

                                if((input[12]^input[13]^input[0]) == xor2[12])
                                {
                                  if((input[13]^input[0]^input[1]) == xor2[13])
                                  {
        				return 1;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
  else
  {
  return 0;
  }
        }

void decrypt(unsigned char* checksum) {
	FILE * f = fopen( "surprise", "wb" );
	long long int max_size = ( sizeof(bin)/8 ) + 16;
	u_int8_t *ptr = malloc( max_size );
	if(f){
    char in = 0;
		for(int i = 0; i <= max_size; i++){

			ptr[i] = bin[i] ^ checksum[i %s 31];
		}
    fwrite( ptr , max_size, 1 , f);
    fclose(f);
		free(ptr);
	}
}
int main(){
    unsigned char input[15], outputBuffer[65];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    int len;
    printf("Enter Key:");
    fgets(input, 15, stdin);
    checksumgen(input, outputBuffer, hash);
    if(check1(input) && check2(input) && strlen(input)==14 ){
        decrypt(hash);
        printf("Surprise!\\n");
        }
    else{
        printf("Need a better key :(\\n");

        }
    }

'''
COMP_X86 = 0
COMP_X64 = 1
COMP_ARM = 2
COMP_ARCH = 3
COMP_PPC = 4

def createbin(src, i, arch):
    with open('template_%d.c' %i, 'w') as f:
        f.write(src)
    if arch == COMP_X86:
        subprocess.call(['gcc', '-fno-stack-protector','-m32', 'template_%d.c' %i, '-s', '-o', 'surprise'])
    elif arch == COMP_X64:
        subprocess.call(['gcc', '-fno-stack-protector', 'template_%d.c' %i, '-s', '-o', 'surprise'])
    elif arch == COMP_ARM:
    	subprocess.call(['arm-linux-gnueabihf-gcc', '-fno-stack-protector', 'template_%d.c' %i, '-o', 'surprise'])
    elif arch == COMP_ARCH:
    	subprocess.call(['aarch64-linux-gnu-gcc', '-fno-stack-protector', 'template_%d.c' %i, '-o', 'surprise']) #or os.system(cmd)
    elif arch == COMP_PPC:
    	subprocess.call(['powerpc64-linux-gnu-gcc-5', '-fno-stack-protector', 'template_%d.c' %i, '-o', 'surprise'])
    else:
        print("BUG")
        exit(-1)
    subprocess.call(['bzip2','-z', 'surprise'])
    subprocess.call(['cp', 'surprise.bz2', 'surprise'])
    subprocess.call(['rm', 'surprise.bz2'])

def alterstring(string):
    val1 = ""
    val2 = ""
    for i in range(len(string)):
        if(i % 2 == 0):
            val1 += string[i]
        else:
            val2 += string[i]
    return (val1 + val2)

def getxorlist(string):
    string = string + string[:2]
    xorvals = [0] * 14
    for i in range(len(string)-2):
#        print(string[i:i+3])
        substr = string[i:i+3]
        val = 0
        for j in substr:
            val = val ^ ord(j)
        xorvals[i] = val
    xorvals = [str(i) for i in xorvals]
    xorval_string = '{' + ', '.join(xorvals) + '}'
    return xorval_string

def gethash(string):
    result = hashlib.sha256(string.encode()).digest()
    checkarr = [str(ord(x)) for x in result]
    checksum_string = '{' + ', '.join(checkarr) + '}'
    return checksum_string, [ord(i) for i in result]


def encryptbin(h):
    i = open('surprise', 'r')
    r = i.read()
    binarr = []
    binstring = ''
    for j in range(len(r)):
        binarr.append(ord(str(r[j])) ^ h[j % (len(h) - 1)])
    binarr=[str(k) for k in binarr]
    binstring = '{' + ','.join(binarr) + '}'
    return binstring
'''
def createbin(src, i):
    with open('template_%d.c' %i, 'w') as f:
		f.write(src)
    subprocess.call(['gcc', '-fno-stack-protector', 'template_%d.c' %i, '-lcrypto', '-lssl', '-s', '-o', 'surprise'])
    subprocess.call(['bzip2','-z', 'surprise'])
    subprocess.call(['cp', 'surprise.bz2', 'surprise'])
    subprocess.call(['rm', 'surprise.bz2'])
'''
def main():
    n = input("enter number of binaries:")
    f = open('inp.txt', 'r')
    strings = f.readlines()
    for i in range(n):
        string = strings[i][:14]
        x1 = getxorlist(alterstring(string))
        print('Generating Binary ' + str(i) + ' '+string)
        x2 = getxorlist(string)
        h ,arr = gethash(string)
        binarr = encryptbin(arr)
        src = template % (x1, x2, binarr, '%')
        createbin(src,i,random.randint(0,4))
        print('Binary ' + str(i) + ' generated')
main()
