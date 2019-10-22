from os import urandom
from Crypto.Cipher import AES
from Crypto.Util.number import *
from hashlib import md5
import hmac

def xor(a, b):
    return "".join([chr(ord(i) ^ ord(j)) for i, j in zip(a, b)])

def pad(m):
    padbyte = 16 - (len(m) % 16)
    return m + padbyte*chr(padbyte)

def unpad(m):
    if ord(m[-1]) < 0 or ord(m[-1]) > 16:
        print "[-] Incorrect padding!"
        sys.exit()
    lastchar = ord(m[-1])
    return m[:-lastchar]

class Cipher:
    def __init__(self, key):
        self.key = key

    def encrypt(self, plaintext, iv):
        plaintext = pad(plaintext)
        temp = iv
        ciphertext = ""
        for i in range(0, len(plaintext), 16):
            aes_obj = AES.new(self.key, AES.MODE_ECB)
            ciphertext_block = aes_obj.encrypt(xor(plaintext[i:i+16], temp))
            ciphertext += ciphertext_block
            temp = md5(ciphertext_block).digest()
        return iv + ciphertext

    def decrypt(self, ciphertext):
        iv = ciphertext[:16]
        ciphertext = ciphertext[16:]
        temp = iv
        plaintext = ""
        for i in range(0, len(ciphertext), 16):
            aes_obj = AES.new(self.key, AES.MODE_ECB)
            plaintext_block = xor(aes_obj.decrypt(ciphertext[i:i+16]), temp)
            plaintext += plaintext_block
            temp = md5(ciphertext[i:i+16]).digest()
        return unpad(plaintext)

class Service:
    def __init__(self, key, secret, p, x, iv):
        self.key = key
        self.secret = secret
        self.p = p
        self.x = x
        self.iv = iv

    def register(self, username, base):
        if "admin" in username:
            return "[-] Invalid username!"
        plaintext = "cookie?username=" + username + "=" + self.secret
        cipher_obj = Cipher(self.key)
        cookie = cipher_obj.encrypt(plaintext, self.iv)
        return cookie.encode("hex") + ":" + self.gen_auth_token(username, base)

    def gen_auth_token(self, username, base):
        if base < 2 or base >= self.p-1:
            return None
        shared_key = long_to_bytes(pow(base, self.x, self.p))
        return long_to_bytes(base).encode("hex") + ":" + hmac.new(shared_key, username).hexdigest()

    def login(self, cookie):
        cookie = cookie.split(":")
        try:
            assert len(cookie) == 3
        except:
            return None
        base = bytes_to_long(cookie[1].decode("hex"))
        auth_token = cookie[2]
        cookie = cookie[0].decode("hex")

        cipher_obj = Cipher(self.key)
        try:
            plaintext = cipher_obj.decrypt(cookie)
        except:
            return None
        plaintext = plaintext.split("=")
        if plaintext[0] != "cookie?username":
            return None
        elif plaintext[-1] != self.secret:
            return None
        elif self.verify_auth_token(plaintext[1], base, auth_token) != True:
            return None
        else:
            return plaintext[1]

    def verify_auth_token(self, username, base, auth_token):
        if base < 2 or base >= self.p-1:
            return False
        shared_key = long_to_bytes(pow(base, self.x, self.p))
        if hmac.new(shared_key, username).hexdigest() == auth_token:
            return True
        else:
            return False
