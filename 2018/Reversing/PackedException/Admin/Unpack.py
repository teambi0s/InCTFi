
#this is the script to unpack PackedException.packed and dump the unpacked binary(PackedException.packed.unpacked)

import sys
import lief
import time
import subprocess
from tqdm import tqdm

def unpack_bin(org_bin, text_offset, text_size, oep):
    print "Unpacking " + org_bin
   
    binary = lief.parse(org_bin)
    header = binary.header
    
    header.entrypoint = oep
    binary.write(org_bin)

    print "Offset reset"

    with open(org_bin, "rb") as f:
        check_pack = bytearray(f.read())

    for i in tqdm(xrange(text_size)):
        check_pack[text_offset + i] ^= 0xa5

    with open(org_bin + ".unpacked", "wb") as f:
        f.write(check_pack)


def main(argv):

    org_bin = argv[1]
    
    unpack_bin(org_bin,0x5b0,0x15eeec,0x400ea0)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
