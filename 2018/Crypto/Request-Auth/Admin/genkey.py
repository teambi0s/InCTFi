from Crypto.PublicKey import RSA
from Crypto.Util.number import *
import gmpy2

p = getPrime(512)
q = getPrime(512)
n = p*q
e = 65537L
phin = (p-1)*(q-1)
d = long(gmpy2.invert(e, phin))

key = RSA.construct((n ,e))
key2 = RSA.construct((n, e, d, p, q))

f = open("publickey.pem","w")
f.write(key.exportKey('PEM'))
f.close()

f2 = open("privatekey.pem","w")
f2.write(key2.exportKey('PEM'))
f2.close()