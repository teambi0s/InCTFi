BITS 16

_start:
	mov ax,07C0h
	mov ds,ax
	mov bx,0x0
	mov cx,0x0

	mov si,string
	call print_string
	call print_input                                            ;to the input character onto the screen

	jmp $

	string db "ENTER THE FLAG",13,10,0
	flag db "w2g1kS<c7me3keeuSMg1kSk%Se<=S3%/e/",13,10,0
	r db "Yeah, that is the flag",13,10,0
	w db "NOOOO",13,10,0
	input db "",10,0
	user_input : resb 45
	xor_input : resb 45
	secret db "0100010011011101111111011010110101",13,10,0
	new : resb 45
	

print_string:
	mov ah,0xe
.loop:
	lodsb
	cmp al,0
	je done
	int 0x10
	jmp print_string

print_input:

	mov ah,0x1
	int 0x16

	mov ah,0x0
	int 0x16

	mov [input],al
	mov byte [user_input + bx],al
	cmp byte[input],13
	je check_len
	inc bx
	mov si,input
	call print_string
	jmp print_input

check_len:                                              ;to check the length of the input
	mov ah,0xe
	mov al,0xa
	int 0x10
	cmp bx,34
	je just
	jmp wrong

just:
	mov ax,0x0
	mov bx,0x0
	mov si,user_input

switch_check:
.loop:
	mov al,0x31
	cmp byte[secret+bx],al
	je lshift
	lodsb
	shr al,0x1
	mov byte[new+bx],al
	inc bx
	cmp bx,35
	je xor
	jmp .loop

lshift:
	lodsb
	shl al,0x1
	mov byte[new+bx],al
	inc bx
	jmp switch_check

some:
	mov si,new
	call print_string

wrong:
	mov ah,0xe
	mov al,0xd
	int 0x10
	mov si,w
	call print_string
	jmp done

right:
	mov ah,0xe
	mov al,0xd
	int 0x10
	mov al,0xd
	int 0x10
	mov al,0xa
	int 0x10
	mov si,r
	call print_string
	jmp done

xor:
	mov bx,0x0
	mov si,new
.xor_input:
	lodsb
	cmp al,0
	je compare
	mov ah,0xe
	xor al,0x5
	mov byte [xor_input + bx],al                              ;moves the xored character to the xor_input string
	inc bx
	jmp .xor_input

compare:                                                    	  ;compares the xor_input with the flag string
	mov bx,33
	mov si,xor_input
.loop:
	lodsb
	cmp al,byte[flag+bx]
	jne wrong
	cmp bx,0
	je right                                                  ;jumps when they are equal
	dec bx
	jmp .loop
done:
	ret
	times 510-($-$$) db 0
	dw 0xAA55
