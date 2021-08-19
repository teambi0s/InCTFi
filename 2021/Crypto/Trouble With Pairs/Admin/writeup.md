# Trouble With Pairs - InCTF Internationals 2021

tl;dr
*   Get **fake_flag** by using Consensus Attack.
*   Get **xored_flag** by forging individual signatures
*   Xor them both to get the **flag**

**Challenge point**: 925

**No. of solves**: 14

**Challenge Author**: [Chandu-Kona](https://twitter.com/chandu_kona?lang=en)

## **Challenge Description**
```
We are testing a new Optimised Signature scheme for Authentication in our Voting System.
This might lead us to reduce the time taken for Election Process.
```

## **Handout**
    -    BLS.py
    -    signer.py
    -    server.py
    
### BLS.py
-    `BLS.py` is same file as `ciphersuites.py` from [py_ecc](https://github.com/ethereum/py_ecc/tree/master/py_ecc/bls) module with a function overriden.
```python
# from py_ecc.bls.hash_to_curve import hash_to_G2
def hash_to_G2(msg, DST, hash):
    m = int(hash(msg).hexdigest(),16)
    return  multiply(G2,m)
```
### signer.py
```python
from BLS import G2ProofOfPossession as bls
from secret import data

result = []
for i in data:
    d = {}
    d['Name'] = i['Name']
    d['Vote'] = i['Vote']
    d['Count'] = i['Count']
    d['PK'] = i['PK'].hex()
    d['Sign'] = bls.Sign(i['PrivKey'],i['Vote'].encode()).hex()
    result.append(d)

# print(result)
'''
[{'Name': 'Nebraska',
  'Vote': 'R',
  'Count': 5,
  'PK': 'aa6fc9c17a1b2de916e5d5453444655e9f6dd3d456b96239f954bc30b80f551c44c1c2423825bc01577e1986098f362b',
  'Sign': 'a09538da373b317adf63cacb53799417ba57d79486aeec78d7687b37e72625190741313800a7698beb2659b725ca728a074514b4cc1fc300dee2e2ae74516993f6760f0839cc4d712a108c58955e062bf45100966fca0288f39f9bfc8ab25706'},
  .
  .
  .
  {'Name': 'Michigan',
  'Vote': 'D',
  'Count': 16,
  'PK': 'ae29e8f4d3c7b814042d04d12930bfc6f78eb12f3b9233a3338fedf42b784b6de6b5d575a0dee6d14de1a5ab9baaf5d9',
  'Sign': 'a977d66e4fabaaa4d79e4d32f6b0d4e2901278d4e0d31e662af8929ac7ca540c377907b7e315b908f5e643e49b4a4fd914d90bb60305595ab6160cfbe0bbabb5c8a98f8ae37fc6af64faf7dbc35a6b55d7e8c3946dda6135a9332f484b818312'}]
'''
```
### server.py
```python
#!/usr/bin/env python3
from BLS import G2ProofOfPossession as bls
from secret import data, bytexor, fake_flag, flag
from json import loads
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


header =    '''We are testing a new Optimised Signature scheme for Authentication in Voting System.

               You can send the Published Result in Specified Format
               Json Format : {'Name' : name, 'Vote' : vote, 'Sign' : signature}
            '''
invalid_json = "Invalid Json!"
invalid_sign = "Invalid signature!"
flag = f"Seems like we could never patch this bug, here is your reward : {bytexor( flag, fake_flag ).hex()}"
fake_flag = f"but, this one is already known, so here is your fake reward : {fake_flag.decode()}"

class Challenge():
    def __init__(self):
        self.data = data
        self.Names = [i["Name"] for i in self.data]
        self.result = []
        for i in range(len(data)):  self.result.append(self.Read(input("> ").strip()))


    def Read(self, inp):
        try:
            data = loads(inp)
            Name = data["Name"]
            Vote = data["Vote"]
            Sign = bytes.fromhex(data["Sign"])

            assert Name in self.Names and Vote in ["R","D"]

            self.data[self.Names.index(Name)]["Vote"] = Vote
            self.data[self.Names.index(Name)]["Sign"] = Sign
        except:
            print(invalid_json)
            sys.exit()


    def Verify_aggregate(self):
        try:
            for j in ["D", "R"]:
                aggregate_sign = bls.Aggregate([i["Sign"] for i in self.data if i["Vote"] == j])
                aggregate_Pk = bls._AggregatePKs([i["PK"] for i in self.data if i["Vote"] == j])
                if not bls.Verify(aggregate_Pk, j.encode(), aggregate_sign):
                    return False
            return True
        except:
            print(invalid_sign)
            sys.exit()


    def Verify_individual(self):
        try:
            return all ( bls.Verify(i["PK"], i["Vote"].encode(), i["Sign"]) for i in self.data)
        except:
            print(invalid_sign)
            sys.exit()


    def Get_Majority(self):
        return max( ["D","R"] , key = lambda j : sum( [ i["Count"] for i in self.data if i["Vote"] == j ] ) )


if __name__ == "__main__":
    print(header)
    challenge = Challenge()

    if challenge.Verify_aggregate():

        if challenge.Get_Majority() == "R":
            print("WOW!!!  You found the bug.")
        else:
            print("Everything is Verified and Perfect.")
            sys.exit()

    else:
        print("Not Verified!")
        sys.exit()

    if challenge.Verify_individual():
        print(flag)
        sys.exit()

    else:
        print(fake_flag)
        sys.exit()
```
## **Observation**
If you had noticed the signing has been done by using bls signatures,
so let's just talk about how BLS works
    
Before we begin, if you are new to ECC pairing, you can refer to this article here: [link](https://medium.com/@VitalikButerin/exploring-elliptic-curve-pairings-c73c1864e627).

### BLS
In 2001, Boneh, Lynn, and Shacham (BLS) invented an elegant signature scheme based on pairing. Let's assume Alice's private key is x, her public key is X = x * G, H be a function which maps the message to point on the elliptic curve E, The signature is simply S = x * H(m) for message m.

To verify, we check whether e(G,S) is equal to e(X,H(m)), 
since we know that:
```
    e(G,S) = e(G,x*H(m)) = e(G,H(m))^x = e(x*G,H(m)) = e(X,H(m))
``` 
### BLS Signature Aggregation
The Bls signature has an attractive security property that is used in Eth2. it allows signature aggregation. Let's assume we have n users, each has Private Key xi, Public key Xi = xi * G (same generator for all users). Each user signs its own message mi as Si = xi * H(mi). Now, in verification, instead of checking n signatures Si individually, we want to verify a single aggregate signature.

To achieve the prious goal,  we compute an aggregate signature S = S1 + S2 + ... + Sn.
To verify S, we chack whether e(G,S) is equal to e(X1,H(m1)) * e(X2,H(m2)) * ... * e(Xn,H(mn)), since we know that:
```
        e(G,S)  = e(G, S1 + S2 + ... + Sn)
                = e(G, x1 * H(m1)) * e(G, x2 * H(m2)) * ... * e(G, xn * H(mn))
                = e(G,H(m1)) ^ x1 * e(G,H(m2)) ^ x2 * ... * e(G,H(mn)) ^ xn
                = e(X1,H(m1)) * e(X2,H(m2)) * ... * e(Xn,H(mn))
```
### Consensus Attacks
At a high level, the attacker's goal is to create a set of invalid individual signatures, but their aggregate signature is valid. Therefore, some users will see valid signatures while others see invalid signatures, i.e., the views among users are split.

Let's say there are 4 messages and signatures:
```
                    m1 = "message1", S1
                    m2 = "message2", S2
                    m3 = "message3", S3
                    m4 = "message4", S4
```
The attacker's goal is to create malicious signatures so that users see malicious signatures but the aggregate verification is valid. The attacker creates the following:
```
                    S1' = S1 - 2P
                    S2' = S2 + P
                    S3' = S3 - P
                    S4' = S4 + 2P
```
where P is a valid point in the subgroup. here if we see the aggregate doesn't change
since:
```
        S1' + S2' + S3' + S4' = S1 - 2P + S2 + P + S3 - P + S4 + 2P
                              = S1 + S2 + S3 + S4 + p - P + 2P - 2P
                              = S1 + S2 + S3 + S4
```
Now we know how BLS works let's get back to the script server.py,
If you had noticed the server takes all the votes and first verify the signatures using the aggregate if you're able to forge successfully then checks the individual signatures for consensus attack, if the server detects any forgery it returns `fake_flag` else it means you successfully braked the system hance it returns `flag`

> Note: we need both `flag` and `fake_flag` since the Original flag is XORed with `fake_flag`.

## Exploit Idea

### Recovering Fake Flag
here, we can make use of **Consensus attack** to recover **fake_flag**, or simply we can swap few signatures to trick the server.
#### In detailed:

```python
def connect(data):
    Host, Port = b'crypto.challenge.bi0s.in', 1337
    io = remote(Host,Port)
    # io = process('./server.py')
    for i in data:
        j = dumps({"Name": i["Name"], "Vote": i["Vote"], "Sign": i["Sign"]})
        io.recvuntil(b'> ')
        io.sendline(j)
    # io.interactive()
    io.recvuntil(b'reward : ')
    return io.recvline().strip()

fake_result = result[:]
w = fake_result[idx+1]
ny = fake_result[idx]
ny["Sign"] = G2_to_signature( add(signature_to_G2(unhex(ny["Sign"])), multiply(signature_to_G2(unhex(w["Sign"])), 2)  )).hex()
w["Sign"] = G2_to_signature( neg( signature_to_G2( unhex(w["Sign"]) ))).hex()
assert bls.Verify(bls._AggregatePKs([unhex(ny["PK"]), unhex(w["PK"])]), b'R', bls.Aggregate([unhex(ny["Sign"]), unhex(w["Sign"])]))
fake_result[idx]   = ny
fake_result[idx+1] = w 

fake_flag = connect(fake_result)
```
> `fake_flag = b'bi0s{7h1s_0n3_1s_n07_7h3_r1gh7_fl4g. :)}'`

### Recovering Flag
here, we can make use of the fualty implementation of `Hash_to_G2` function in `BLS.py`, since H(m) = sha256(m)*G ; S = x * H(m) and we know m, we can take the inverse of sha256(m) and cancell it out and now multiply our desired message hash to forge, or simply we can multiply sha256(desired message) with PublicKey X since X = x * G and sha256(dm)*X = x*sha256(dm)*G

#### In detailed:
```python
def bytexor(data,pad):
    assert len(data) == len(pad)
    return bytes(i^j for i,j in zip(data,pad))

order = 52435875175126190479447740508185965837690552500527637822603658699938581184513
m1,m2 = [int(sha256(i).hexdigest(),16) for i in [b"D",b"R"] ]
idx,ny = [(i,j) for i,j in enumerate(result) if j["Name"] == 'New York' ][0]
ny["Sign"] = G2_to_signature( multiply( multiply( signature_to_G2( unhex(ny["Sign"]) ), invert(m1,order)), m2)).hex()
ny["Vote"] = "R"
assert bls.Verify(unhex(ny["PK"]) ,ny["Vote"].encode() ,unhex(ny["Sign"]) )
result[idx] = ny

xored_flag = unhex(connect(result).decode())

flag = bytexor(fake_flag,xored_flag)
```

## Exploit
```python
from hashlib import sha256
from os import remove
from BLS import G2ProofOfPossession as bls
from py_ecc.bls.g2_primitives import G2_to_signature, signature_to_G2
from py_ecc.optimized_bls12_381 import add, multiply, neg
from gmpy2 import invert
from json import dumps
from signer import result
from pwn import *

unhex = lambda i : bytes.fromhex(i)

context.log_level = 'debug'

def bytexor(data,pad):
    assert len(data) == len(pad)
    return bytes(i^j for i,j in zip(data,pad))

def connect(data):
    Host, Port = b'crypto.challenge.bi0s.in', 1337
    io = remote(Host,Port)
    # io = process('./server.py')
    for i in data:
        j = dumps({"Name": i["Name"], "Vote": i["Vote"], "Sign": i["Sign"]})
        io.recvuntil(b'> ')
        io.sendline(j)
    # io.interactive()
    io.recvuntil(b'reward : ')
    return io.recvline().strip()



order = 52435875175126190479447740508185965837690552500527637822603658699938581184513
m1,m2 = [int(sha256(i).hexdigest(),16) for i in [b"D",b"R"] ]
idx,ny = [(i,j) for i,j in enumerate(result) if j["Name"] == 'New York' ][0]
ny["Sign"] = G2_to_signature( multiply( multiply( signature_to_G2( unhex(ny["Sign"]) ), invert(m1,order)), m2)).hex()
ny["Vote"] = "R"
assert bls.Verify(unhex(ny["PK"]) ,ny["Vote"].encode() ,unhex(ny["Sign"]) )
result[idx] = ny

xored_flag = unhex(connect(result).decode())

fake_result = result[:]
w = fake_result[idx+1]
ny = fake_result[idx]
ny["Sign"] = G2_to_signature( add(signature_to_G2(unhex(ny["Sign"])), multiply(signature_to_G2(unhex(w["Sign"])), 2)  )).hex()
w["Sign"] = G2_to_signature( neg( signature_to_G2( unhex(w["Sign"]) ))).hex()
assert bls.Verify(bls._AggregatePKs([unhex(ny["PK"]), unhex(w["PK"])]), b'R', bls.Aggregate([unhex(ny["Sign"]), unhex(w["Sign"])]))
fake_result[idx]   = ny
fake_result[idx+1] = w 

fake_flag = connect(fake_result)


flag = bytexor(fake_flag,xored_flag)

print(flag)

assert flag == b'inctf{BLS_574nd5_f0r_B0n3h_Lynn_Sh4ch4m}'

```

## Flag
> `flag = b'inctf{BLS_574nd5_f0r_B0n3h_Lynn_Sh4ch4m}'`