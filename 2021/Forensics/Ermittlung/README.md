# Ermittlung

### Description

Our Incident Response team started their investigation on a device found when pinning down a terrorist. They got some doubts while analyzing the device, So they framed these questions can you help them in answering these questions? Our Intelligence report states that the terrorist used a legit chat application for communication among themselves.

* What is the name of the chat application program?
    * Ex: `Mozilla_Firefox` (Use Name of the program, Not the name of the binary. If there is a space replace it with `_`. )

* When did the user last used this chat application?
    * Answer in `DD-MM-YYYY_HH:MM:SS`. Timestamp in UTC

* How many unread messages are there in the chat application that the user is using?
    * Answer should be an integer `n`.

* What is the current version of the chat application that's being used?
    * Answer in `X.X.XXXX.XXXX`

**Note:** 
+ Wrap the answers around inctf{}.
+ Sample flag: `inctf{Mozilla_Firefox_31-07-2020_19:00:00_10_1.2.2345.5678}`
+ Flag is **Case Sensitive**

**Challenge file**: 

+ [Google Drive](https://drive.google.com/drive/folders/1mwjdM44ZySk4HZG-aDY880MoqAdFjPkZ?usp=sharing)
+ [Mega](https://mega.nz/file/cxsB1QyI#sIdIH4vmzSfcBJdaz74NYhzIin6hWCLFm1pq3qZuV-E)

**MD5 Hash**: `ermittlung.raw 110305F3CF71432B4DFAFD1538CDF850`

### Short Writeup

* Name of the chat application - **Outlook Express**

* HKEY_CURRENT_CONFIG\Software\Microsoft\Windows\CurrentVersion\Explorer\UserAssist\{75048700-EF1F-11D0-9888-006097DEACF9}\count

    * msimn.exe - Main executable for Outlook Express - **27-07-2020 12:26:17 UTC**

* HKEY_CURRENT_CONFIG\Software\Microsoft\Windows\CurrentVersion\UnreadMail\danial.banjamin@gmail.com

    * The subkey **Message Count** gives the count of unread messages. ie: **4**

* HKEY_CURRENT_CONFIG\Software\Microsoft\Outlook Express\5.0\Shared Settings\Setup

    * The Subkey **MigToLWPVer** gives the current usage version of Outlook Express.
    * Version - **6.0.2900.5512**

### Flag

`inctf{Outlook_Express_27-07-2020_12:26:17_4_6.0.2900.5512}`

### Author

[g4rud4](https://twitter.com/_Nihith) (Nihith)

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/16/Forensics/Ermittlung-InCTF-Internationals-2021/)
+ [g4rud4's blog](https://g4rud4.gitlab.io/2021/Ermittlung-InCTF-Internationals-2021/)