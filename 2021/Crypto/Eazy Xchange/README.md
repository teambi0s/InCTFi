# Eazy Xchange

### Description

My older brother found a new way to implement the DH Key Exchange. I tried my best to recreate his method. Hope I didn't make a mistake...

**Challenge file**: 
+ [Google Drive](https://drive.google.com/file/d/1ecoAFhDc2rfUgrFbnXykoxveUqAWNGZI/view?usp=sharing)
+ [Mega](https://mega.nz/file/BjZmkRLJ#EV13r061yTDGH6638AADdnPlRlz0sOeDf6VoB9EZ7cI)

**MD5 Hash**: `src.zip 677edcba5b74a91d090abb46cfffb095`

### Short Writeup

* Challenge Files given:-
    - main.sage
    - enc.pickle

* The challenge describes a Diffie-Hellman Key Exchange using ECC.

* The flaw in the system is in the **exponentiation** of the private key with the public key.

* Instead of using a large variable the function multiplies bytes and adds them together. This results in a reduced size key than expected.

* The key can easily be brute-forced in \~5mins.

### Flag

`inctf{w0w_DH_15_5o_c00l!_3c9cdad74c27d1fc}`

### Author

Alekh (xxMajinxx)