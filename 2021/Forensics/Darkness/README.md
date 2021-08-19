# Darkness

### Challenge Description

We have recieved the report that certain employee of an organization might have stolen confidential information and hidden in his system. We seized his laptop and collected a forensic image of the system. Our intel suggest that the employee might have visited suspicious websites and also deleted key files from the system which could've been vital for us. Could you please recover it? 

**Challenge File**:
+ [Google Drive](https://drive.google.com/file/d/1vPGSUFxB6XO5zWsYATjDEr0ubAWrDiAD/view?usp=sharing)
    + Password: `d:'2;]7{<-v5^4]tz@*s+%qqd}c|&mv]`

**MD5 Hash**: `1256e5319b3cf0da4699e93be47e6612 Evidence.7z`

### Short Writeup

1. The zip file is actually deleted from disk and can be recovered by extracting the Volume shadow copy from the .E01.
2. Checking the browser history tells us that the employee visited pastebin but the exact paste link is not present (Basically the employee deleted a part of the history to cover his tracks).
3. MS Windows has a feature to collect Diagnostic Data which is optional. The data collected includes MS Edge Browser History, Installed programs info and much much more.
4. To extract the DB from the system, navigate to `C:\ProgramData\Microsoft\Diagnosis\EventTranscript\EventTranscript.db` and extract the file. Make sure to extract the -wal file too because that contains our required URL. Write Ahead Log files basically are used to maintain DB data and are written to original DB when system shuts down. That is why -wal file is important here.
5. Open the DB using any DB viewer and to view the browser history (Table - Events_presisted) and set the column filter logging_binary_name = msedge.exe.
6. In the payload section, as you dig into it, you observe the field "navigationUrl" contains the pastebin link - https://pastebin.com/cvRK3yY5
7. Navigate to the URL and supply the password obtained from the recovered deleted file

### Flag

inctf{th1s_d4y_w3_d1sc0veR3d_4_N3w_4R7iFaCt}

### Author

Abhiram Kumar (stuxn3t)
