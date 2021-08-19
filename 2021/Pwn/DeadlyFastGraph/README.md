# DeadlyFastGraph

### Challenge Description

I decided that DFG wasn't fast enough.

**Challenge Files** 

+ [DFGHandout.zip](./Handout/DFGHandout.zip)

### Short Writeup

Removal of a `CheckStructure` node in DFG's Constant Folding Phase allows for an arbitrary type confusion, that can only be triggered for one JITed function. Abuse this to get arbitrary r/w.

### Author

d4rk_kn1gh7

### Flag

`inctf{JIT_t0o_f4st_1t_g0t_c0nfus3d}`

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/15/Pwn/InCTFi21-DeadlyFastGraph/)
