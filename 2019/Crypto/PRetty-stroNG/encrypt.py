#!/usr/bin/env python2.7

from Crypto.Cipher import AES
from Crypto.Util.number import *
from hashlib import *
import sys,random,os
from secret import FLAG,secret,messages



class Unbuffered(object):
   def __init__(self, stream):
       self.stream = stream
   def write(self, data):
       self.stream.write(data)
       self.stream.flush()
   def writelines(self, datas):
       self.stream.writelines(datas)
       self.stream.flush()
   def __getattr__(self, attr):
       return getattr(self.stream, attr)

sys.stdout = Unbuffered(sys.stdout)

class PRNG(object):
    def __init__(self, seed1, seed2):
            self.seed1 = seed1
            self.seed2 = seed2

    @staticmethod
    def rotl(x, k):
            return ((x << k) & 0xffffffffffffffff) | (x >> 0x40 - k)

    def next(self):
            s0 = self.seed1
            s1 = self.seed2
            result = (s0 + s1) & 0xffffffffffffffff

            s1 ^= s0
            self.seed1 = self.rotl(s0, 0x37) ^ s1 ^ ((s1 << 0xe) & 0xffffffffffffffff)
            self.seed2 = self.rotl(s1, 0x24)

            return result


def left_right(num):
    num = (((num & 2863311530) >> 1) | ((num & 1431655765) << 1))
    num = (((num & 3435973836) >> 2) | ((num & 858993459) << 2))
    num = (((num & 4042322160) >> 4) | ((num & 252645135) << 4))
    num = (((num & 4278255360) >> 8) | ((num & 16711935) << 8))
    return((num >> 16) | (num << 16))


def wrapper(x):
    a = left_right(x/(2**32))
    b = left_right(x%(2**32))
    return (a << 64) + b


def Encryption_Box(message):
    m = bytes_to_long(message)
    h = pow(g, secret, p)
    y = wrapper(gen.next())
    c1 = pow(g, y, p)
    s = pow(h,y,p)
    c2 = (m*s) % p
    return hex(c1),hex(c2)

def Decryption_Box(c1,c2):
    s = pow(c1,secret,p)
    m = (c2*inverse(s,p))%p
    message = long_to_bytes(m)
    if message in messages:
        return message
    return "Nice Try!"

def Super_Encrypion_Box(key):
    key = sha256(long_to_bytes(key)).digest()
    aes = AES.new(key,AES.MODE_CBC,md5(key).digest())
    ct = aes.encrypt(FLAG)
    return ct.encode('hex')


if __name__=="__main__":

    g = 2
    p = 7199773997391911030609999317773941274322764333428698921736339643928346453700085358802973900485592910475480089726140708102474957429903531369589969318716771
    seed1 = bytes_to_long(os.urandom(8))
    seed2 = bytes_to_long(os.urandom(8))
    gen = PRNG(seed1,seed2)

    print "[1] Encryption Box"
    print "[2] Super Encryption Box"
    print "[3] Decryption Box"
    print "[4] Exit"

    for _ in range(30):
        try:
            ch = int(raw_input('Enter option > '))
        except:
            print "Error!"
            sys.exit()
        if ch == 1:
            random.shuffle(messages)
            print "Here is your Encrypted Message:", Encryption_Box(messages[0])
        elif ch == 2:
            print "Here is your flag:", Super_Encrypion_Box(gen.next())
        elif ch == 3:
            try:
                c1 = raw_input("Enter first ciphertext c1 (in hex): ")
                c2 = raw_input("Enter second ciphertext c2 (in hex): ")
                c1 = int(c1,16)
                c2 = int(c2,16)
                print "Here is your message:", Decryption_Box(c1,c2)
            except:
                print "Wrong Input !!"
                sys.exit()
        elif ch == 4:
            print "Bye!"
            sys.exit()
        else:
            print "Error!"
            sys.exit()
