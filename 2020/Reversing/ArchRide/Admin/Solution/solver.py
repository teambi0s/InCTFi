from z3 import *
import r2pipe
import subprocess
import os

def uncompress():
    subprocess.call(['rm','surprise.out'])
    subprocess.call(['bzip2', '-d','surprise'])
    
#Function to obtain values from offsets from each binary
def get_xorvalues(arch):
    r = r2pipe.open("surprise.out")
    offsets={ "4":0x10020130, "0":[0x0202020,0x0202060], "2":[0x3020,0x3060] , "1":0x011008, "3":0x0012010}#need to recheck offsets for each arch before running script
    if arch == '0' or arch == '2':
        arch_offset1='pf 14d @'+str(offsets[arch][0])
        arr = r.cmd(arch_offset1) #offset has to checked with ida after every 20 iters when the arch of the binary changes
        arr=[int(i) for i in arr.strip().split()[5::7]]
        xor1=arr
        arr=[]
        arch_offset2='pf 14d @'+str(offsets[arch][1])
        arr = r.cmd(arch_offset2) #offset has to checked with ida after every 20 iters when the arch of the binary changes
        arr=[int(i) for i in arr.strip().split()[5::7]]
        xor2=arr
        print(xor1,xor2)
        return xor1,xor2
    else:
        print(offsets[arch],arch)
        arch_offset='pf 28d @'+str(offsets[arch])
        arr = r.cmd(arch_offset) #offset has to checked with ida after every 20 iters when the arch of the binary changes
        arr=[int(i) for i in arr.strip().split()[5::7]]
        xor1=arr[:14]
        xor2=arr[14:]
    print(xor1,xor2)
    return xor1,xor2
#Using z3 to solve each binary with the values extracted using r2pipe
def z3solve(xor1,xor2):
    #xor1=[92, 106, 0, 110, 89, 67, 116, 73, 93, 92, 113, 116, 67, 57]
    #xor2=[40, 30, 106, 61, 61, 93, 96, 97, 111, 127, 73, 66, 83, 73]
    s=Solver()
    for i in range(0, 14):
        globals()['a[%i]' % i] = BitVec('a[%i]' % i, 8)
        s.add(globals()['a[%i]' % i] >= 48)
        s.add(globals()['a[%i]' % i] <= 122)
    s.add(globals()['a[0]']^globals()['a[2]']^globals()['a[4]']==   xor1[0])
    s.add(globals()['a[2]']^globals()['a[4]']^globals()['a[6]']==   xor1[1])
    s.add(globals()['a[4]']^globals()['a[6]']^globals()['a[8]']==   xor1[2])
    s.add(globals()['a[6]']^globals()['a[8]']^globals()['a[10]']==  xor1[3])
    s.add(globals()['a[8]']^globals()['a[10]']^globals()['a[12]']== xor1[4])
    s.add(globals()['a[10]']^globals()['a[12]']^globals()['a[1]']== xor1[5])
    s.add(globals()['a[12]']^globals()['a[1]']^globals()['a[3]']==  xor1[6])
    s.add(globals()['a[1]']^globals()['a[3]']^globals()['a[5]']==   xor1[7])
    s.add(globals()['a[3]']^globals()['a[5]']^globals()['a[7]']==   xor1[8])
    s.add(globals()['a[5]']^globals()['a[7]']^globals()['a[9]']==   xor1[9])
    s.add(globals()['a[7]']^globals()['a[9]']^globals()['a[11]']==  xor1[10])
    s.add(globals()['a[9]']^globals()['a[11]']^globals()['a[13]']== xor1[11])
    s.add(globals()['a[0]']^globals()['a[11]']^globals()['a[13]']== xor1[12])
    s.add(globals()['a[13]']^globals()['a[0]']^globals()['a[2]']==  xor1[13])
    s.add(globals()['a[0]']^globals()['a[1]']^globals()['a[2]']==   xor2[0])
    s.add(globals()['a[1]']^globals()['a[2]']^globals()['a[3]']==   xor2[1])
    s.add(globals()['a[2]']^globals()['a[3]']^globals()['a[4]']==   xor2[2])
    s.add(globals()['a[3]']^globals()['a[4]']^globals()['a[5]']==   xor2[3])
    s.add(globals()['a[4]']^globals()['a[5]']^globals()['a[6]']==   xor2[4])
    s.add(globals()['a[5]']^globals()['a[6]']^globals()['a[7]']==   xor2[5])
    s.add(globals()['a[6]']^globals()['a[7]']^globals()['a[8]']==   xor2[6])
    s.add(globals()['a[7]']^globals()['a[8]']^globals()['a[9]']==   xor2[7])
    s.add(globals()['a[8]']^globals()['a[9]']^globals()['a[10]']==  xor2[8])
    s.add(globals()['a[9]']^globals()['a[10]']^globals()['a[11]']== xor2[9])
    s.add(globals()['a[10]']^globals()['a[11]']^globals()['a[12]']==xor2[10])
    s.add(globals()['a[11]']^globals()['a[12]']^globals()['a[13]']==xor2[11])
    s.add(globals()['a[12]']^globals()['a[13]']^globals()['a[0]']== xor2[12])
    s.add(globals()['a[13]']^globals()['a[0]']^globals()['a[1]']==  xor2[13])

    if (s.check() == sat):
        values =s.model()
    res = ""
    for i in range(0,14):
        obj = globals()['a[%i]' % i]
        c = values[obj].as_long()
        res = res + chr(c)
    print(res)
    return(res)

def getnew_bin(res,arch):
    cmd={"4":'qemu-ppc64 surprise.out',"1":'qemu-arm -L /usr/arm-linux-gnueabihf surprise.out',"3":'qemu-aarch64-static surprise.out','0':'./surpise.out','2':'./surpise.out'}
    cmd='echo "'+res +'"|'+ cmd[arch]
    #to fix libc issues emulating different archs
    if(arch == '4'):
        os.system('cp /path/to/libc/ppc_libc /lib64/libc.so.6')
        os.system('chmod +x surprise.out')
        os.system(cmd)
        os.system('cp /path/to/libc/arm_libc /lib64/libc.so.6')
    else:
        os.system('chmod +x surprise.out')
        os.system(cmd)
        os.system('cp /path/to/libc/arm_libc /lib64/libc.so.6')
#This function gets the arch of eah binary using file command
def get_arch():
    result = subprocess.check_output('file surprise.out', shell=True)
    result=result.strip().split()
    arch = -1
    if(result[2]=='64-bit' and result[6]=='x86-64,'):
        arch = 0
    if(result[2]=='32-bit' and result[6]=='ARM,'):
        arch = 1
    if(result[2]=='32-bit' and result[6]=='Intel'):
        arch = 2
    if(result[2]=='64-bit' and result[6]=='ARM'):
        arch = 3
    if(result[2]=='64-bit' and result[6]=='PowerPC'):
        arch = 4
    print(result)
    print(result[2],result[6])
    return str(arch)

def main():
    n=input("Number of binaries")#120
    for i in range(int(n)):
        arch=get_arch()
        uncompress()
        xor1,xor2=get_xorvalues(arch)
        res=z3solve(xor1,xor2)
        getnew_bin(res,arch)

main()
