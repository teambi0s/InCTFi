# Tabula Recta

### Challenge Description

X made a stateless password manager and used it for all the top sites he visited. But on observing the code he found that his key could retrieve a maximum number of state and decided to not use it because of its weaknesses.

However, he did not get to reset all of his passwords.

We'll send you the names of some websites at `nc 34.106.211.122 1222`. If you are able to find most of the passwords, we'll give you the flag

**Challenge File**:
+ [Handout.zip](./Handout/Handout.zip)

### Short Writeup

+  Table generation using extremely weakened version of RC4 as per paper by [Fluhrer, Mantin and Shamir](https://link.springer.com/content/pdf/10.1007%2F3-540-45537-X_1.pdf). The KSA is b-conversing
+  Key generation leads to conditions that might give a special b-exact key.
+  Reversing the given password using simple Matrix operations would give the first 12 output bytes of the cipher
+ generate possible b-exact keys and check against the first table entries generated
+ Use the key to re-generate table. re-generate passwords for the websites at netcat to get the flag
### Flag

inctf{Always_h4v3_a_statistic4l_3y3_wh3n_it_com3s_to_weakn3ss3s}

### Author

[ph03n1x](https://twitter.com/MeenakshiSl1), [4l3x1](https://twitter.com/SandhraBino)
