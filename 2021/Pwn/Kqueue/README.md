# Kqueue

### Description

A long queue awaits you in ring0.

**Challenge Files**

+ [kqueue](./Handout/Handout.zip)

**MD5 Sum**: bzImage - `d7c173966e9fb6e79eaef8d351cb8f09`

### Short Writeup

Use the integer overflow to trigger a controlled heap overflow , arrange an overflowing chunk above the `tty` structure with the help of fake userspace meta data. Get kernel instruction pointer by partial overwrite, arrange shellcode by offsetting from a register having kernel code address.

### Challenge Author

Cyb0rG

### Flag

`inctf{l3akl3ss_r1p_w1th_u5erSp4ce_7rick3ry}`

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/17/Pwn/InCTFi21-Kqueue/)
