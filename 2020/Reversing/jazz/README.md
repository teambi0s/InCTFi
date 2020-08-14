# jazz

### Challenge Description

"Advanced Super Secure Cipher" - Rust Go With It!

### Short Writeup

The challenge implements a simple variant of Substitution Cipher where multiple tables are created using a seeded random function. The challenge can be solved in multiple ways, either by creating the tables using the same seed, by dumping the tables or by running a single byte brute force. To make it less obvious that a single byte brute force is possible, AES encryption with known key was added at the end.
The challenge was a Rust release binary. Making the reversing process more challenging than usual.

### Challenge Author

k4iz3n

### Flag

```
inctf{fly_m3_70_7h3_m00n_l37_m3_pl4y_4m0n6_7h3_574r5_4nd_l37_m3_533_wh47_5pr1n6_15_l1k3}
```
