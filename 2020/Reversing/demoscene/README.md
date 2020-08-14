# Demoscene

### Challenge Description

it is all in the timing

### Short Writeup

Compiled using --> 
```
clang -mllvm -bcf  -mllvm -sub_loop=3 -mllvm -aesSeed=B105B105B105B105B105B105B105B105 chall.c -o cryptor_obfus.exe 
```
Use disassembler and find the xor. Decrypt wut and you will get an executable.
Single function XOR with ollvm - Encryptor.
Gluttony timer function - Demoscene.

### Challenge Author

Freakston, Silv3rfelix

### Flag

```
inctf{thisaintframestutter}
```
