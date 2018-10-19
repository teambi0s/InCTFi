# InCTF 2018

This Instance contains two challenges :
- krev part 1
- krev part 2

## krev part 1
You can find the first challenge kernel module in /root/chall1
 
## krev part 2
You can find the second challenge in /root/chall2. The second challenge also contains a skeleton code which can be used to communicate with the kernel module.

## Inserting kernel module
We have not inserted the kernel module. You can insert it and remove it according to your wish using the following commands from the respective folders

Inserting the kernel module (modload requires the complete path)-
`modload /root/chall1/chall1.kmod`
`modload /root/chall2/chall2.kmod`

Removing the kernel module (modunload requires the module name only)-
`modunload chall1`
`modunload chall2`

Incase you need to create nodes -
`mknod /dev/chall1 c 210 0`
`mknod /dev/chall2 c 211 0`

## Other Points

- This instance of NetBSD has ssh enabled - you can copy your code via ssh.
- You can compile your c code here with gcc <filname> -o <outputfilename>
