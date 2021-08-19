# Right Now Generator

### Description

I just made the fastest RNG! No one can predict my machine.

**Challenge file**: 
+ [Google Drive](https://drive.google.com/file/d/1VQxysawGNDNOnSOO3rg-KOlekHEkOiAm/view?usp=sharing)
+ [Mega](https://mega.nz/file/4yo1mCLL#tOXOqa-QbyYxEqF6lmnzQgK3C6w8yTqSzdtlpn3Jtmc)

**MD5 Hash**: `source.zip 154bdd0484f005f6326a2c87e96a0672`

### Short Writeup

* Challenge Files given:-
    - main.py
    - enc.pickle

* The challenge describes a RNG similar to MT19937.

* The flaw in the system is that the next value generation can easily be reversed.

* Next the seed updation process is predictable.

* These flaws allows an attacker to guess the previous outputs as well as the future outputs.

### Flag

`inctf{S1mpl3_RN65_r_7h3_b35t!_b35e496b4d570c16}`

### Author

Alekh (xxMajinxx)