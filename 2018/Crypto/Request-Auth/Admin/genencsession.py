from os import urandom
from Crypto.Cipher import AES
from Crypto.PublicKey import RSA
from Crypto.Util.number import *

def pad(s):
    padlen = 16 - (len(s) % 16)
    return s + padlen*chr(padlen)

key = urandom(16)
print "AES key: ", key.encode("hex")
f = open("key.txt",'w')
f.write(key)

iv = open("iv.txt").read()

obj1 = AES.new(key, AES.MODE_CBC, iv)
session_enc = obj1.encrypt(pad("bi0s:userid=1:user=inctf{y0u_eff1ng_CCA2_w1nn3r}"))
open("session.enc",'w').write(session_enc)

pubkey = RSA.importKey(open("publickey.pem").read())
n = pubkey.n
e = pubkey.e
open("key.enc",'w').write(long_to_bytes(pow(bytes_to_long(key), e, n)))
