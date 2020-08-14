#!/usr/bin/env python -u

import os, sys, string
import random
from hashlib import sha256

def proof_of_work(level=4):
    """
    Proof of work script to challenge users with
    
    :param level -> int: Difficulty level of POW challenge 

    :returns -> bool: Challenge response status
    """
    
    challenge = "".join([random.choice(string.digits + string.ascii_letters) for i in range(20)])
    digest = sha256(challenge.encode()).hexdigest()
    
    print("sha256(" + "X" * level + "+%s) == %s" \
            % (challenge[level:], digest)
    )
    print("Give me " + "X" * level + ": ")
    response = sys.stdin.read(level)
    if len(response) != level or response != challenge[:level]:
        return False
    return True

if __name__ == "__main__":
    if not proof_of_work():
        exit(0)
    else:
        exit(1)


