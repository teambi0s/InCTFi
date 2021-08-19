# Heist

Our Intelligence Bureau team found out a group of people roaming around a well-noted organization, and our team has captured them. After the interrogation, Our IB team found out the head of the heist they planned. While capturing the leader of the heist, Our team found some electronic devices like laptops, USB devices. Our evidence collection team captured the data from these devices and sent it to us for analysis. During evidence collection, The team found out that the leader of the heist was using a lot of browsers, remote desktop applications, Voice modulators etc. Our team needs some help from you in finding answers to some questions. Can you help the team in finding answers to these questions?

**Questions:**

1. What is the default browser that the Heist leader is using on the device?
    
    * Ex: `Opera_Mini`, etc (Use Name of the program, Not the name of the binary. If there is a space replace it with `_`)
2. What is the top-visited website in the leader's system on the default browser?
    
    * Answer in `domain.net` (`HTTP(s)://` or `www.` & sub-domains are NOT included)
3. When was the latest file transfer session initiated in TeamViewer?
    
    * Answer in `DD-MM-YYYY_HH:MM:SS`. Timestamp in UTC
4. What is the ID, Hostname of that file-transfer session?
    
    * Format: `123456789_Hostname`

**Note**:

1. Wrap the answers around inctf{}.
2. Sample Flag: `inctf{Opera_google.com_01-01-2012_01:01:10_123456789_Hostname}`

**Challenge File**: 
+ [Google Drive](https://drive.google.com/drive/folders/1H3Ly8hnAW7eh7dxvf_bTA7_JYk8zMP3-?usp=sharing) - Splitted Files(Not password protected).
+ [OneDrive](https://amritauniv-my.sharepoint.com/:u:/g/personal/inctfj_am_amrita_edu/EbF0I2jKpPNAj9pQ0ORQX-UBLqGCpw0XpKtrWze1tgxB0Q?e=m3W0ZN) - Password Protected 7Zip.
    + Password: `NWUyOWQ2NmM3NWI1MDdkMmIxMjY`

**MD5 Hash**: 
+ `31f23c78ff99142bad2a778db6a64163 Heist.E01`
+ `A916E26016180D2C5189061D652DC9E1 Heist.7z`

### Short Writeup

1. From the NTUSER.DAT, we can find the default browser of the system.
    + Hive Location: `NTUSER.DAT: Software\Microsoft\Windows\Shell\Associations\UrlAssociations\{http|https}\UserChoice`.
    + We get Chrome as the default browser.

2. As we got the default browser, we can go check the TopSites Sqlite Database present in `Users/Danial Benjamin/AppData/Local/Google/Chrome/User Data/Default/` and sort it with URL rank we get **`ebay.com`**

4. On comparing `Connections_incoming.txt` and `Connections.txt` present in Teamviewer's appdata folder, we got the time File transfer session was initiated.
    + Time initiated: `20-07-2021_07:48:50`

5. We can find the ID and Hostname from the `Connections_incoming.txt` present in Teamviewer's appdata folder.
    + ID_Hostname: `920981533_DESKTOP-S34NLCJ`

### Flag

inctf{Google_Chrome_ebay.com_20-07-2021_07:48:50_920981533_DESKTOP-S34NLCJ}

### Author

[g4rud4](https://twitter.com/_Nihith) (Nihith)

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/16/Forensics/Heist-InCTF-Internationals-2021/)
+ [g4rud4's blog](https://g4rud4.gitlab.io/2021/Heist-InCTF-Internationals-2021/)