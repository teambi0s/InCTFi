#!/usr/bin/env python2.7

from Crypto.Util.number import *
from os import urandom
import ecdh
from secret import secretkey, n
import sys

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


b = 41058363725152142129326129780047268409114441015993725554835256314039467401291
p = 2**256 - 2**224 + 2**192 + 2**96 - 1
a = p-3
curve = ecdh.CurveFp(p, a, b)

print colors.orange + "Starting Handshake..." + colors.reset
print colors.orange + "Send me the base point coordinates\n" + colors.reset
try:
    _Px = int(raw_input("x-coordinate of the base point P (in hex without 0x): "), 16)
    _Py = int(raw_input("y-coordinate of the base point P (in hex without 0x): "), 16)
except:
    print colors.red + "\nGive me a valid input!" + colors.reset
    sys.exit()

sk = secretkey
assert sk < n

point_P = ecdh.Point(curve, _Px, _Py, n)
assert point_P*n == ecdh.INFINITY

publickey = ecdh.Public_key(point_P, sk*point_P)
print "Here, take my public key: ", publickey
print colors.blue + "\nNow that you have my public key, give me your public key" + colors.reset
try:
    _Qx = int(raw_input("x-coordinate of the point Q = <your_secret_key> * P (in hex without 0x): "), 16)
    _Qy = int(raw_input("y-coordinate of the point Q = <your_secret_key> * P (in hex without 0x): "), 16)
except:
    print colors.red + "\nGive me a valid input!" + colors.reset
    sys.exit()
point_Q = ecdh.Point(curve, _Qx, _Qy, n)
print colors.green + "\nConnection Ending..." + colors.reset
