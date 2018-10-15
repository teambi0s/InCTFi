import sys
import string

def xor(s):

	a = ''.join(chr(ord(i)^3) for i in s)
	return a


def encoder(x):
	
	return x.encode("base64")


if __name__ == "__main__":

	f = open("C:\\Users\\hello\\Desktop\\vip.txt", "w")

	arr = sys.argv[1]

	arr = encoder(xor(arr))

	f.write(arr)

	f.close()
