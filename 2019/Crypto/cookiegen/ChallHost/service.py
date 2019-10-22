import os
import sys
from cookiegen import Service
from secret import key, iv, secret, x, flag

p = 337333846325195852023465984016735747017640658020735865443882234978293187151183899366894634062588357161

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

print "Welcome to CookieGen service!"
print "[1] Register"
print "[2] Login"
choice = int(raw_input("Select if you want to login or register: "))
if choice == 1:
    username = raw_input("Enter your username: ")
    if "admin" in username:
        print "[-] Invalid username!"
        sys.exit(0)
    base = int(raw_input("Enter your base for authentication token: "))
    if base < 2 or base >= p-1:
        print "[-] Invalid base value!"
        sys.exit(0)
    service_obj = Service(key, secret, p, x, iv)
    print "Here, take your cookie and auth token: ", service_obj.register(username, base)
elif choice == 2:
    session_cookie = raw_input("Enter your cookie along with auth token: ")
    service_obj = Service(key, secret, p, x, iv)
    username = service_obj.login(session_cookie)
    if username == None:
        print "Invalid session cookie or auth token!"
    elif username != "admin":
        print "Welcome ", username
    else:
        print "Welcome admin! Here, take you flag", flag
