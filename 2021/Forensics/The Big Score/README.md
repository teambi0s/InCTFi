# The Big Score

## Challenge Description

We sent Michael over to the Union Depository to collect data from one of their systems for the heist. We were able to retrieve the data, but it looks like they were able to read the message sent to us that Michael had typed from their system. Fortunately, he took the memory dump before escaping the building. Analyze the memory dump and find out how the message was compromised.

**Challenge Link :**
+ [Google Drive 1](https://drive.google.com/drive/folders/1JZfwuASJ9e8LVWcB4py59AB7kxrKEKFK?usp=sharing)
+ [Google Drive 2](https://drive.google.com/drive/folders/1qzVvBS29lh8VwHWnmyqLscg0p11t8Vz3?usp=sharing)

**MD5 Hash :** 5bdcfc3d4a73020019fc61ab6e933395

### Short Write-up

+ Build Linux profile for Ubuntu 18.04 (linux-headers-5.4.0-42-generic)
+ Use `linux_bash` plugin in Volatility to recover memfd_create malware payload and decode it to retrieve the github link. (Alternate : Dump the malicious process to retrieve the github link)
+ Analyzing the code given in the repository, recover the `/bin/log` file from the memory dump using `linux_find_file` in Volatility and brute-force the specific hash to retrieve the file path in `termbin`.
+ Decode the keyboard stream data in order to retrieve the flag.

### Flag

inctf{th1s_1s_the_b1g_oNe_lester}

### Author

[d3liri0us](https://twitter.com/d3liri0us_) (Pranav)
