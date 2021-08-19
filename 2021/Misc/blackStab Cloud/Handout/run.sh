#!/bin/bash
service mysql start
mysql -u root -e "CREATE DATABASE blackStab"
mysql -u root blackStab < /opt/blackStab/users.sql
sed -i 's/0.0.0.0/127.0.0.1/g' /etc/mysql/my.cnf
python3 /opt/blackStab/server.py