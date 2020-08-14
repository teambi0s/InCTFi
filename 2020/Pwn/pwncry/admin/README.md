# Pwncry

Compilation: gcc -o revamp -fPIC -pie -g -Wl,-z,relro,-z,now revamp.c -L /usr/lib/ssl -lssl -lcrypto

working envt: Ubuntu 16.04

OpenSSL version required: 1.0.2g
