#!/usr/bin/python

from pwn import *
import sys

binary = ['./jsc',
    '--useConcurrentJIT=false',
    './exp.js']

if len(sys.argv) > 1:
    io = remote("localhost", 5555)
    f = open("./exp.js", "r")
    data = f.read()
    io.sendlineafter(">>\n", str(len(data)))
    io.send(data)
    io.interactive()

else:
    io = process(binary)
    io.interactive()