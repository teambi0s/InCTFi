#!/bin/sh

NAME=rack1
PASS=brutablebrutablebrutablepasssssss
FOLDER="/ftp/$NAME"

echo -e "$PASS\n$PASS" | adduser -h $FOLDER -s /sbin/nologin $NAME
mkdir -p $FOLDER
chown $NAME:$NAME $FOLDER
MIN_PORT=21000
MAX_PORT=21010
exec /usr/sbin/vsftpd -opasv_min_port=$MIN_PORT -opasv_max_port=$MAX_PORT /etc/vsftpd/vsftpd.conf