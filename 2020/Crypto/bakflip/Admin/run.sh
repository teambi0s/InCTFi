#!/bin/bash

HOME=/home/ctf
cd $HOME
python3 pow.py
if [ $? -eq 1 ]
then
    timeout 120 python3 challenge.py
fi

