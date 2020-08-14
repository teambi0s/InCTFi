#!/usr/bin/env python2
import random
import sys
from stuff import flag


def ROL32(x, y):
    return (((x) << (y)) ^ ((x) >> (32 - (y)))) & 0xFFFFFFFF


def LSB(x):
    return x & 0x00000000FFFFFFFF


def TIMES2(x):
    if (x & 0x8000000000000000):
        return ((x << 1) ^ 0x000000000000001B) & 0xFFFFFFFFFFFFFFFF
    else:
        return (x << 1) & 0xFFFFFFFFFFFFFFFF


def TIMES4(x):
    return TIMES2(TIMES2(x)) & 0xFFFFFFFFFFFFFFFF


def MIX(hi, lo, r):
    hi += (lo & 0xFFFFFFFF)
    lo = ROL32(lo, r)
    lo ^= (hi & 0xFFFFFFFF)
    return hi & 0xFFFFFFFF, lo & 0xFFFFFFFF


def PERM64(x):

    rcon = [1, 29, 4, 8, 17, 12, 3, 14]
    hi = x >> 32
    lo = LSB(x)

    for i in range(32):
        hi, lo = MIX(hi, lo, rcon[i % 8])
        lo += i
    return ((hi & 0xFFFFFFFFFFFFFFFF) << 32) ^ lo


def EMR64(k, p):
    return PERM64(k ^ p) ^ k


def encrypt(key, n, m, x):

    l = TIMES4(EMR64(key, n))
    c = EMR64(key, l ^ m) ^ x
    return c


if __name__ == "__main__":

    secret_key = random.getrandbits(64)
    x = random.getrandbits(64)

    for _ in range(140):
        print "[1] Encrypt"
        print "[2] Get Flag"
        print "[3] Exit"

        try:
            ch = int(raw_input('\nEnter option > '))
        except Exception as e:
            print "Error!", e
            sys.exit()

        if ch == 1:
            try:
                off = int(raw_input('\nEnter offset for key > '))
                n = int(raw_input('\nEnter Parameter n > '))
                m = int(raw_input('\nEnter Message > '))
               
                m = m & 0xFFFFFFFFFFFFFFFF
                c = encrypt(secret_key + off, n, m, x)
                print "\nCiphertext: ", hex(c).strip('L')
            except:
                print "Something went wrong!"
                sys.exit()

        elif ch == 2:
            try:
                secret = int(raw_input('Enter Secret Key > '))
            except:
                print "Error!"
                sys.exit()
            if secret == secret_key:
                print "Here is your Flag [+] ", flag

            else:
                print "Wrong Secret!"
                sys.exit()


        elif ch == 3:
            print "Bye!"
            sys.exit()
        else:
            print "Error!"
            sys.exit()
