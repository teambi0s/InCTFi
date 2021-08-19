# Trouble With Pairs

### Challenge Description
   We are testing a new Optimised Signature scheme for Authentication in our Voting System.
   
   This might lead us to reduce the time taken for Election Process.
   
   `nc crypto.challenge.bi0s.in 1337`

**Challenge Files**:

+ [Google Drive](https://drive.google.com/file/d/1EUQZyfZLIoml-5CEdpzKCvKdEo5Sm84d/view?usp=sharing)
+ [Mega](https://mega.nz/file/VB5E3aIT#NHUxwjXMlhxF9uqrfpztfUui0IKWkSMURVVjpo4eT0A)

**MD5 Hash**: `Handout.zip 16a91c9a58605aefc8855e8564b2decd`

### Short Writeup

*   Challenge Files given:-
    -   server.py
    -   signer.py
    -   BLS.py
*   The challenge is about BLS Signature aggregation, it has 2 bugs
*   1st one is about Consensus Attack, for this they need add and subrtact few signatures such that the sum will remain same.
*   After completeting the previous step successfully they get a fake_flag, which is used to xor the Original flag
*   Now, The 2nd vulnerability is about the implementation, they need to read BLS.py and understand the wrong implementation and forge some signatures to get xored flag.
*   Now, They have to xor both fake flag and xored flag to get the flag

### Flag
`inctf{BLS_574nd5_f0r_B0n3h_Lynn_Sh4ch4m}`

### Author

[**Chandu-kona**](https://twitter.com/chandu_kona)
