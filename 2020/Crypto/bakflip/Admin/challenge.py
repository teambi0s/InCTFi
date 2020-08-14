#!/usr/bin/env python3

import random, sys
from binascii import hexlify, unhexlify
from ecdsa import SigningKey, NIST192p
from flag import flag

secret_multiplier = random.getrandbits(101)

def menu():
    menu = [exit, signMessage, verifyMessage, getFlag, sys.exit]

    print("""
    bakflip&sons Signature Scheme

        1) Sign Message
        2) Verify Signature
        3) Get Flag
        4) Exit
    [ecdsa@cryptolab]# """, end = "")

    choice = int(input())
    menu[choice]()

def signMessage():
    print("""
    Sign Message Service - courtsy of bakflip&sons
    """)

    message = input("Enter a message to sign: ").encode()
    if message == b'please_give_me_the_flag':
        print("\n\t:Coughs: This ain't that easy as Verifier1")
        sys.exit()
    secret_mask = int(input("Now insert a really stupid value here: "))

    secret = secret_multiplier ^ secret_mask

    signingKey = SigningKey.from_secret_exponent(secret)
    signature = signingKey.sign(message)
    print("Signature: ", hexlify(signature).decode())


def verifyMessage():
    raise(
        NotImplementedError(
            "Geez! We are working round the clock to get this Beetle fixed."
        )
    )

def getFlag():
    print("""
    BeetleBountyProgram - by bakflip&sons

        Wanted! Patched or Alive- $200,000
        Submit a valid signature for 'please_give_me_the_flag' and claim the flag
    """)
    signingKey = SigningKey.from_secret_exponent(secret_multiplier)
    verifyingKey = signingKey.verifying_key
    try:
        signature = unhexlify(input("Forged Signature: "))
        if verifyingKey.verify(signature, b'please_give_me_the_flag'):
            print(flag)
    except:
        print("Phew! that was close")

       
if __name__=="__main__":
    for i in range(73): menu()
