# wARMup 

**Challenge files** : [handout](Handout/)

**Author** : night_f0x

**Short Solution** : There is a 16 bytes stack overflow. since ASLR is disabled in qemu , the address of system will be constant. Leaking ones will reveal the address of the libc. Create ROP chain to call system with `/bin/sh` as an argument.
