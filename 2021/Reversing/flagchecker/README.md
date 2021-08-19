# flagchecker

### Challenge Description

Enter the correct flag in correct flag format.

### Short Writeup

+  Vm challenge asks for the flag. Each character of the flag(when taken as 0x{ascii val}) points to a a number in mem. Group of 4/5 characters of the flag, and the value pointed by them in mem is stored in an array which is passed to func where there is a switch case which inturn calls multiple forks. The correct order of the values in the array, gives a string which is then compared to check the flag. To find the correct order, we understand that the parent process's output for each set of 4/5 char will always be at the end(thanks to multiple wait checks in the functions). If we figure this out, we figure out the path it takes checking which all numbers that are being appended into the check file from the parent. That narrows it down a lot. And then try out the different path that parent takes out of those.

### Flag

inctf{vM_W1ht_l0t7_0f_pRoces5ES9902}

### Author

[imm0rt4l_5t4rk](https://twitter.com/SimranKathpalia)
