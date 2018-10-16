from Crypto.PublicKey import RSA
from Crypto.Util.number import *
from Crypto.Cipher import AES

def unpad(s):
    s = s[:-ord(s[len(s) - 1])]
    return s

privkey = RSA.importKey(open("privatekey.pem").read())
pubkey = RSA.importKey(open("publickey.pem").read())
pn = pubkey.n
pe = pubkey.e
n = privkey.n
d = privkey.d
e = privkey.e

assert pn == n
assert pe == e

key_AES = bytes_to_long(open("key.enc").read())
key_AES = long_to_bytes(pow(key_AES, d, n))
iv = open("iv.txt").read()

session_enc = open("session.enc").read()
print key_AES.encode("hex")
obj1 = AES.new(key_AES, AES.MODE_CBC, iv)
print unpad(obj1.decrypt(session_enc))
