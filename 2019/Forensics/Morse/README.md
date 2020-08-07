# "...---..."

I recently bought a MiBand and started exploring what crazy stuff I can do with it. Maybe this capture helps you find it yourself.

Note: Please submit the flag as inctf{sha1(FLAG IN CAPITALS)}

**Challenge file archive**: [Google drive](https://drive.google.com/file/d/1P4FzZKSdl_sWuXKuXBpVrfSJAnT6TScy/view)

**Authors**: [f4lc0n](https://twitter.com/theevilsyn)

**Short solution**

+ Alert signals encoded in morse transfered to the Mi-Band.
+ Traverse through the packets and find the appropriate BLE handles of the encoded message.
+ Decode the morse encoded message.

**Writeup**

+ [blog.bi0s.in](https://blog.bi0s.in/2019/10/10/Forensics/InCTF-Internationals-2019/)