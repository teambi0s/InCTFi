#!/usr/bin/env python2.7

from Crypto.PublicKey import RSA
from Crypto.Util.number import *
import gmpy2
import sys

def get_e(N, p, q):
    e = getRandomInteger(30)
    while GCD(e, (p-1)*(q-1)) == 1:
        e += 1
    assert GCD(e, (p-1)*(q-1)) != 1
    return e

def prima(p):
    while not isPrime(p):
        p += 1
    assert isPrime(p)
    return p

def gen_publickey(sz):
    while True:
        coeff = getRandomInteger(5)
        p = getPrime(1024)
        q = coeff*p + getRandomInteger(512)
        p = prima(p)
        print "size(p): ", size(p)
        q = prima(q)
        print "size(q): ", size(q)
        print ""
        N = p*q
        e = get_e(N, p, q)
        return (e, N, p, q)

e1, N1, p1, q1 = gen_publickey(1024)
e2, N2, p2, q2 = gen_publickey(1024)

# Exporting private key for admin
priv_key = RSA.construct((N1, e1, None, p1, q1))
priv_key2 = RSA.construct((N2, e2, None, p2, q2))
open("privatekey1.pem","w").write(priv_key.exportKey("PEM"))
open("privatekey2.pem","w").write(priv_key2.exportKey("PEM"))

# Exporting public keys
pub_key = RSA.construct((N1, e1))
pub_key2 = RSA.construct((N2, e2))
open("publickey1.pem","w").write(pub_key.exportKey("PEM"))
open("publickey2.pem","w").write(pub_key2.exportKey("PEM"))

flag = open("flag.txt",'r').read()
flag_num = bytes_to_long(flag)
ct1 = pow(flag_num, e1, N1)
ct2 = pow(flag_num, e2, N2)

print "ciphertext1: ", ct1
print "ciphertext2: ", ct2
f1 = open("ciphertext1.txt", 'w')
f2 = open("ciphertext2.txt", 'w')
f1.write(long_to_bytes(ct1))
f2.write(long_to_bytes(ct2))
