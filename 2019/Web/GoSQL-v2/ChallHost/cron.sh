#! /bin/bash
find /var/www/html/Challenges/InCTF-2019/GoSQL-v2/tmp/ -mmin +0.05 -type f -exec rm {} \; 
