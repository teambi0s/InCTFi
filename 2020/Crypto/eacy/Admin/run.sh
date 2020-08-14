#!/bin/bash

HOME=/home/ctf
cd $HOME
python pow.py
if [ $? -eq 1 ]
then
    timeout 200 python encrypt.py
fi

