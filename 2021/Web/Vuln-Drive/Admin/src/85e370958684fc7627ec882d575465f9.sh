#!/bin/bash

service mysql start
mysql < dump.sql
sleep 3
rm dump.sql
service apache2 restart
rm /var/www/html/index.html
cd /app
source env/bin/activate
export LOC='flag'
gunicorn --bind 0.0.0.0:5000 wsgi:app &
while :
do
	export LOCA=$LOC
	export LOC=$(cat /dev/urandom | head | md5sum | cut -d " " -f 1)
	mv /$LOCA /$LOC
	echo "USE challenge;UPDATE adminfo SET path = '/$LOC' WHERE name = 'Admin';" | mysql
	rm -rf /app/uploads/*
	sleep 10m
done
