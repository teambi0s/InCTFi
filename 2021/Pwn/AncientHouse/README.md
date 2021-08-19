# Ancient House

### Challenge Description

Someone's gotta stop those glibc nerds (the challenge runs the DEBUG build of jemalloc)

**Challenge Files** 

+ [Ancienthouse](./Handout/Ancienthouse)
+ [libjemalloc.so](./Handout/libjemalloc.so)
+ [jemalloc-2.2.5.tar.bz2](./Handout/jemalloc-2.2.5.tar.bz2)

### Short Writeup

Since freed memory is not cleared by jemalloc , controlled regions can be placed appropriately to achieve info leak.
Overwrite `MAXALLOC` using negative indexing. Fill the arena that lies before the region holding the function ptr . Abuse the buggy implementation of `strncat` used during merge to overwrite the next run header, to then get overlapping chunks.

### Author

Pwn-Solo

### Flag

`inctf{h0us3_0f_th3_f4lse_k1ngd0m}`
