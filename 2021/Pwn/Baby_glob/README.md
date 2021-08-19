# Baby Glob

### Challenge Description

Super secure path finder from your own 2017.

#### md5sum

chall - `60aedc6cf9a7b163254cfc2ffea64c04`

**Challenge Files** 

+ [glob](./Handout/Handout.zip)

### Short Writeup

The glob function used is vulnerable to [CVE-2017-15804](https://sourceware.org/git/?p=glibc.git;a=blobdiff;f=posix/glob.c;h=cb39779d0716d430b0580d2493f56e38f832cb79;hp=15a6c0cf13bdccb7972183884f87c5d4be2a2f1b;hb=a159b53fa059947cc2548e3b0d5bdcf7b9630ba8;hpb=914c9994d27b80bc3b71c483e801a4f04e269ba6) which is basically a heap overflow caused during improper `GLOB_TILDE` unescaping.

### Author

Cyb0rG

### Flag

`inctf{CVE-2017-15804_Subtl3_H3ap_Overfl0w}`

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/17/Pwn/InCTFi21-Baby_Glob/)
