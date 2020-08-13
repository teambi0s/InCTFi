import sys 
import uuid
import os
import subprocess 
import string
import random
import base64
from hashlib import sha256

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



def proof_of_work(level: int =4) -> bool:
    challenge = "".join([random.choice(string.digits + string.ascii_letters) for i in range(20)])
    digest = sha256(challenge.encode()).hexdigest()
    
    print("sha256(" + "X" * level + "+%s) == %s" \
            % (challenge[level:], digest), 
            flush=True
    )
    response = sys.stdin.read(level)
    if len(response) != level or response != challenge[:level]:
        return False
    return True

def run_and_get_output(command):
    try:
        out = subprocess.check_output(command, shell=True, stderr=subprocess.STDOUT)
        return out
    except Exception as e:
        print("Some error running the pass!")
        exit(-1)

def main():
    if not proof_of_work():
        exit(0)
    print("Give the Base64 encoded bitcode file (clang 10) : ")
    binary = sys.stdin.readline()

    try:
        filename = os.path.join("/tmp", str(uuid.uuid4()))
        fp = open(filename, "wb")
        fp.write(base64.b64decode(binary))
        fp.close()
    except Exception as e:
        print("invalid input.. Exiting")
    
    out = run_and_get_output("./opt -f -load ./AO1tt.so -getflag < %s > /dev/null" % filename)
    print("Your output : ")
    print(out.decode("utf-8"))

if __name__ == "__main__":
    sys.stdout = Unbuffered(sys.stdout)
    main()
