push rbp /* 0x13337000 - first breakpoint */
mov rbp, rsp  /* 0x13337001 */  
xor rax, rax  /* 0x13337004 */ 
xor rbx, rbx  /* 0x13337007 */
xor rcx, rcx  /* 0x1333700a */
xor rdx, rdx /* 0x1333700d - second breakpoint */
mov eax, 0x13337009 /*  + 1 */
mov ecx, 0x9090c3c9
mov dword [eax], ecx
jmp $-26
leave
ret

8² + 4³ = 2⁷

push rbp /* 0x51dd0000 */
mov rbp, rsp /* 0x51dd0001 */
mov al, 8 /* 0x51dd0004 */
mov bl, 4 /* 0x51dd0006 */
mov cl, 2 /* 0x51dd0008 */
leave
ret