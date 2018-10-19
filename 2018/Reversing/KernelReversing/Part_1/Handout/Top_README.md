# InCTF 2018 KREV - Part 1 and 2

Your Intro into NetBSD kernel module reversing :)

The following components have been supplied with this challenge
- An Netbsd hard disk with the challenge modules present in their directory.
- run.sh to start the provided instance.
- Gdb compiled for debugging NetBSD kernel.
- netbsd.gdb file for kernel debugging symbols.
- Kernel modules for chall 1 and chall 2 in the respective folders.

## Connecting to qemu via ssh

If you are using run.sh then you can connect to the netbsd instance using the following command
`ssh root@localhost -p 5022 -v`

The password is mentioned below.

# GDB TIPS

To connect gdb to the NetBSD kernel. You need to run `./run.sh -s -S`. This will make qemu wait for a gdb stub.

You need to run gdb `./debug.sh`. This will load the debugging symbols of the kernel into gdb. Now in gdb run `target remote:1234`. This should connect gdb to the netbsd instance provided.

Now you can use gdb as usual.

# Running the NetBSD 

You can run the run.sh file in two ways
- `./run.sh` - For normal run purpose
- `./run.sh -s -S` - For kernel debugging purpose

More information on the challenges can be found in a README.md in the /root directory of the OS

# LOGIN CREDENTIALS

We have setup a root password for the system.
- USERNAME - root
- PASSWORD - inctf

# Reversing tips
NetBSD source code is available online. Below are a couple of links you can refer to incase they are required at any point.

- https://github.com/NetBSD/src/  - NetBSD source code
- https://nxr.netbsd.org   - NetBSD code search engine
- https://man-k.org    - NetBSD man page search engine

