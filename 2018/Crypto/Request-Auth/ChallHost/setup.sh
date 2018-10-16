#!/bin/sh

groupadd -r $1 && useradd -r -g $1 $1
mkdir /home/$1
cp /home/ubuntu/run.sh /home/$1/
cp /home/ubuntu/ServerSide.py /home/$1/

chown -R root:$1 /home/$1
chmod 750 /home/$1

touch /home/$1/flag
cp /home/ubuntu/iv.txt /home/$1/
cp /home/ubuntu/privatekey.pem /home/$1/

chown root:$1 /home/$1/flag
chown root:$1 /home/$1/iv.txt
chown root:$1 /home/$1/privatekey.pem

chmod 440 /home/$1/flag
chmod 440 /home/$1/iv.txt
chmod 440 /home/$1/privatekey.pem
