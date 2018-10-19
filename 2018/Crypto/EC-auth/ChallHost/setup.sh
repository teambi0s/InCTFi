#!/bin/sh

groupadd -r $1 && useradd -r -g $1 $1
mkdir /home/$1
cp /home/ubuntu/run.sh /home/$1/
cp /home/ubuntu/ecsession.py /home/$1/
cp /home/ubuntu/ecauth.py /home/$1/
cp /home/ubuntu/secret.py /home/$1/

chown -R root:$1 /home/$1
chmod 750 /home/$1
