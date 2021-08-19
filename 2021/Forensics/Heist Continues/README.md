# Heist Continues

Our analyst team at Intelligence Bureau need answers for few more questions. Can you help them out in finding answers?

**Questions:**

1. What is the workspace ID and USER ID of the Slack workspace that is the user participating in?
    
    * Answer in `T0A0A0A0A0A_U0A0A0A0A0` (All in Uppercase)

2. There was a remote connection and we think there is a secret text on the remote connected PC's wallpaper. What are the first and last 3 characters of the secret text?
    
    * Format: `abcxyz`
3. Team restored 2 USB devices (Sandisk 3.2Gen1 & Toshiba External USB 3.0) at the leader's place. What is the file system of these 2 USB devices?
    
    * Format: `FileSystem1_FileSystem2` (All in caps)
4. Team found some traces of Voice Modulator, How much time did the user actively used this Voice Modulator?
    
    * Answer in `X` Seconds.

**Note**: 

+ Wrap the answers around inctf{}.
+ **Sample Flag**: `inctf{T0A0A0A0A0A_U0A0A0A0A0_abcxyz_FileSystem1_FileSystem2_X}`
+ The **challenge file** is same as that of **Heist** challenge.
+ Flag is **Case Sensitive**

### Short Writeup

1. We can go through **000004.log** file present in `Users/Danial Benjamin/AppData/Roaming/Slack/Local Storage/leveldb/000004.log`. We will get,
    + Workspace ID: T027GM97WJ3
    + USER ID: U027XK55WCT
2. AnyDesk stores the wallpaper present on the remote PC as a thumbnail. We can get the thumbnail by checking out this folder `Users/Danial Benjamin/AppData/Roaming/AnyDesk/thumbnails`.
    + First and last 3 characters: `a27da2`.
3. Decoding the hex present in Vbr0 present in `Microsoft-Windows-Partition-Diagnostic.evtx`.
    + `FAT32_NTFS`
4. We find the duration of how much time the user used a particular application from ActivityCache.db present at `C:\Users\%profile name%\AppData\Local\ConnectedDevicesPlatform\%profile name%\`.
    + We will see 4 instances of Voicemod used at different intervals. Adding all the active durations we get `800`.

### Flag

inctf{T027GM97WJ3_U027XK55WCT_a27da2_FAT32_NTFS_800}

### Author

[g4rud4](https://twitter.com/_Nihith) (Nihith)

### Writeup

+ [blog.bi0s.in](https://blog.bi0s.in/2021/08/16/Forensics/Heist-Continues-InCTF-Internationals-2021/)
+ [g4rud4's blog](https://g4rud4.gitlab.io/2021/Heist-Continues-InCTF-Internationals-2021/)