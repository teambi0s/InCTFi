#!/usr/bin/env python2.7

from Crypto.Cipher import AES
from Crypto.PublicKey import RSA
from Crypto.Util.number import *
from os import urandom
import sys

BLOCKSIZE = 16

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

class colors:
    reset='\033[0m'
    red='\033[31m'
    green='\033[32m'
    orange='\033[33m'
    blue='\033[34m'

def unpad(s):
    s = s[:-ord(s[len(s) - 1])]
    return s

def check_valid_request(s):
    try:
        s = s.split(":")
    except:
        return False
    if len(s) != 3:
    	return False
    if s[0] != "bi0s":
    	return False
    if s[1][:7] != "userid=":
    	return False
    if s[2][:5] != "user=":
    	return False
    return True

class ServerSide:
    def __init__(self, key, iv):
        self.key = key[-16:]
        self.iv = iv[-16:]

    def process_request(self, req_enc):
        try:
            obj2 = AES.new(self.key, AES.MODE_CBC, self.iv)
            request = obj2.decrypt(req_enc)
            return check_valid_request(request)
        except:
            return False


def get_AES_key():
    try:
        key_enc = raw_input("Enter encrypted key value in hex: ")
        key_enc = int(key_enc, 16)
    except:
        print colors.red + "Enter valid input!" + colors.reset
        sys.exit()
    priv_key = RSA.importKey(open("privatekey.pem").read())
    n, d = priv_key.n, priv_key.d
    key_AES = pow(key_enc, d, n)
    key_AES = long_to_bytes(key_AES)
    return key_AES


string1 = colors.blue + """
$$\       $$\  $$$$$$\\
$$ |      \__|$$$ __$$\\
$$$$$$$\  $$\ $$$$\ $$ | $$$$$$$\\
$$  __$$\ $$ |$$\$$\$$ |$$  _____|
$$ |  $$ |$$ |$$ \$$$$ |\$$$$$$\\
$$ |  $$ |$$ |$$ |\$$$ | \____$$\\
$$$$$$$  |$$ |\$$$$$$  /$$$$$$$  |
\_______/ \__| \______/ \_______/
""" + colors.reset
if __name__ == '__main__':
    print colors.orange + "Welcome to bi0s Request Validation Service" + colors.reset
    print string1
    key = get_AES_key()
    iv = open("iv.txt").read()
    obj1 = ServerSide(key, iv)

    try:
        ct = raw_input("\nEnter value of encrypted session request in hex: ")
        ct = ct.decode("hex")
    except TypeError:
        print colors.red + "Enter a valid hex string!" + colors.reset
        sys.exit()

    if obj1.process_request(ct) == True:
        print colors.green + "\nValid request!" + colors.reset
    else:
        print colors.red + "\nInvalid request!" + colors.reset
