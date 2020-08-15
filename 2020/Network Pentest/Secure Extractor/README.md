## **Golden Page**

### **Challenge description**

An intern who works at our company made an application which he calls the Supreme Extractor, we strongly believe that the application is vulnerable and we also got to know that he pushed it to production without deleting his history.

Link: http://172.30.0.4:5000


### **Short writeup**

+ Archive a malicious tar file with symlinks as it's contents.
+ Read the user's bash history by uploading the malicious tar with symlink to the histfile path.
+ Login to the user's machine with the password.
+ Read the cronjobs
+ Spoof IP and host a malicous debian package which will be downloaded by the cronjob inside box.
+ Wait for cron to install it and give you a root shell.


### **Author**

[Jaswanth Bommidi](https://twitter.com/theevilsyn)