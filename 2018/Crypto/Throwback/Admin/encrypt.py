from Crypto.Util.number import *
import gmpy2

def make_pubpri(nbit):
    p, q, r = [ getPrime(nbit) for _ in xrange(3)]
    n = p * q * r
    phi = (p-1)*(q-1)*(r-1)
    l = min([p, q, r])
    d = getPrime(1 << 8)
    e = inverse(d, phi)
    a = getPrime(2*nbit)
    while True:
        g = getRandomRange(2, a)
        if pow(g, 2, a) != 1 and pow(g, a/2, a) != 1:
            break
    return (n, e), (n, d)

pubkey, privkey = make_pubpri(512)
#print "Public key: ", pubkey
#print "Private key: ", privkey
f = open("key_parameters.txt",'w')
f.write("n: " + str(privkey[0]) + "\n")
f.write("d: " + str(privkey[1]) + "\n")
f.write("e: " + str(pubkey[1]))

print "n: ", privkey[0]
print "d: ", privkey[1]
print "e: ", pubkey[1]