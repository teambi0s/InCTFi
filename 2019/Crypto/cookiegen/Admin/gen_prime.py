from Crypto.Util.number import *

list1 = [137L, 149L, 173L, 38723L, 39659L, 44351L, 49253L, 51131L, 52361L, 53693L, 57557L, 62039L, 63667L, 63367L, 44729L]
p = 307411825630649691581756682253429535160
x = reduce(lambda x, y: x*y, list1)
print "x: ", x
print "prime p: ", (p*x) + 1

assert isPrime(p*x + 1) == True

p_factors = [8, 3, 5, 7, 53, 4951, 13175982811, 105849660277041952303L]
assert reduce(lambda a, b: a*b, p_factors) == p
assert isPrime(reduce(lambda a, b: a*b, p_factors) * reduce(lambda x, y: x*y, list1) + 1) == 1
