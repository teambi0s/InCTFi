# MD-Notes

### Challenge Description

Here's a nice web application to host your notes. 

**Challenge File**:
[source](./Handout/md-notes.zip)

**MD5 Hash**: `ca05235cf495a7bf889136415d9f006e`

### Short Writeup

+ Leak admin’s hash using wildcard target origin in postMessage or by calculating sha256('').
+ Create an XSS payload to read /api/flag and send it to attacker server.

### Flag

`inctf{8d739_csrf_is_fun_3d587ec9}`

### Author

[Imp3ri0n](https://twitter.com/YadhuKrishna_)

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/14/Web/InCTF-internationals-MD-Notes/)