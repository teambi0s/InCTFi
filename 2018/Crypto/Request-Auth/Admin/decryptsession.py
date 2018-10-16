from Crypto.Cipher import AES
from Crypto.PublicKey import RSA
from Crypto.Util.number import *

privkey = RSA.importKey(open("privatekey.pem").read())
d = privkey.d
n = privkey.n

iv = open("iv.txt").read()
sessionenc = open("session.enc").read()
keyenc = bytes_to_long(open("key.enc").read())
key = long_to_bytes(pow(keyenc, d, n))

obj1 = AES.new(key, AES.MODE_CBC, iv)
print obj1.decrypt(sessionenc)
