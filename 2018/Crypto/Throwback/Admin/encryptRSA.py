from Crypto.PublicKey import RSA
from Crypto.Util.number import *

key = RSA.importKey(open("public.pem").read())
n = key.n
e = key.e
flag = bytes_to_long(open("flag.txt").read())
ct = long_to_bytes(pow(flag, e, n))
open("ciphertext.txt",'w').write(ct)
