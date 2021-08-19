# Heist Ends

### Challenge Description

Our IB team recovered a mobile phone from one of the members of the gang. Can you help out the team in finding answers for the following questions?

**Questions**:

1. When did the Professor create the note for Rio?
    * Answer in `DD-MM-YYYY_HH:MM:SS`. Timestamp in UTC

2. Where did Professor and Rio, planned to meet for planning the heist?
    * Format: `Lat_Long` (round-off to 3 decimals)

3. When did Rio plan to meet Professor?
    * Answer in `DD-MM-YYYY_HH:MM:SS`. (In original timezone)

4. How many members did Rio gathered for the heist?
    * Format: `N` (Integer)

5. How many tasks did Rio created in planning the heist, and how many did he complete?
    * Format: `Created_Completed` in Integers

6. There is a secret code present in a document shared between Rio & Professor, can you find out what it is?
    * Format: `AB1234578PMFE`

7. We found a game installed on the device. When did Rio first open this game?
    * Answer in `DD-MM-YYYY_HH:MM:SS` in UTC

**Note**:
+ Wrap the flag around inctf{}
+ Sample flag: `inctf{01-01-2012_14:01:16_1.111_2.222_01-01-2012_14:01:00_1_0_0_AB1234578PMFE_01-01-2012_14:01:00}`
+ Flag is **Case Sensitive**

**Challenge File**: 
+ [Google Drive](https://drive.google.com/file/d/1hLgFoXYQA-brR8ucAKJa3lCRx94XXXRD/view?usp=sharing)
+ [OneDrive](https://amritauniv-my.sharepoint.com/:u:/g/personal/inctfj_am_amrita_edu/Ecfnrp8zcZdHsd-7PhCaP1ABxCZBo2qOPNM7AGQL1WnGhw?e=g25yfA)

**MD5 Hash**: `Heist_ends.zip 28EB446FB1A2D3B408CBCCAFBBFBA86D`

### Short Writeup

+ Extract creation timestamp of a note from Google Keep Notes.
+ Finding location, date & time from Slack Messages.
+ Extract no. of tasks completed and created from Google Tasks.
+ Finding secret code from Google Docs cache.
+ Extract first opened timestamp of a Game.

### Flag

inctf{19-07-2021_12:28:39_13.108_80.225_20-07-2021_21:00:00_11_4_3_MintMMCT15AUG_20-07-2021_12:03:49}

### Author

[g4rud4](https://twitter.com/_Nihith) (Nihith)

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/16/Forensics/Heist-Ends-InCTF-Internationals-2021/)
+ [g4rud4's blog](https://g4rud4.gitlab.io/2021/Heist-Ends-InCTF-Internationals-2021/)
