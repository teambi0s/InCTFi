from random import Random
from flag import flag ,seeds
from Crypto.Cipher import AES
from hashlib import sha256


SECRET = 14810031
#assert seeds[3]%seeds[1] == 0 CLUE-1
def generate() :
    masks = [43, 578, 22079, 142962]
    for i in range(4) :
        assert (masks[i].bit_length() == seeds[i].bit_length()) == True
    

    l = [lfsr(seeds[i],masks[i],masks[i].bit_length()) for i in range(4)]
    data = ''
    for i in range(10000) :
        data += str(combine(l[0].next(),l[1].next(),l[2].next(),l[3].next()))
    f = open('rem_data','w')
    f.write(data[160:])
    f.close()
    return data[:160]

class lfsr():
    def __init__(self, init, mask,masklength):
        self.rand = Random()
        self.rand.seed(SECRET + mask)
        self.init = init
        self.mask = mask
        self.masklength = masklength


    def next(self):
        r  = self.rand.getrandbits(20)
        nextdata = ((self.init << 1)&0xffffff) ^ (self.mask & r)
        output = 0
        l = nextdata.bit_length()
        for i in range(0,l//2,2) :
            output += int(bin(nextdata)[2:][i])
            self.init = nextdata ^ output
        return output%2

def combine(a,b,c,d) :
    return (a^b)^(a|c)^(b|c)^(c|d)

def enc() :
    f = flag.ljust(16*((len(flag)/16)+1),'0')
    key = sha256(generate()).digest()
    return AES.new(key,AES.MODE_ECB).encrypt(f)

if __name__ == "__main__" :
    f = open('flag.enc','w')
    f.write(enc())
    f.close()
