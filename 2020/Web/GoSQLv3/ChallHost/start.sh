#!/bin/sh
while [ true ]
do
    python /home/spyd3r/delete_functions.py
    python /home/spyd3r/database_checker.py > /dev/null 2>&1
    sleep 10
done

