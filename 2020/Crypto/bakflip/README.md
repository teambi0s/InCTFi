# bakflip&sons

### Challenge Description

Double, double toil and trouble;
Fire burn and caldron bubble.

`nc bakflip.crypto.inctf.in 9999`
### Short Writeup

    Exploit Technique in 4 steps
    1> Recover the Public Key form a message, signature pair
    2> Apply bit flipping attack and recover 70 msbits of the secret
    3> Perform Pollard Lambda with the known bounds on d
    4> Forge the signature with the recovered d

### Long Writeup

See the [exploit script here](Admin/exploit.py)

>  `sage -ipython exploit.py`

### Challenge Author

v4d3r

### Flag

inctf{i_see_bitflip_i_see_family}
