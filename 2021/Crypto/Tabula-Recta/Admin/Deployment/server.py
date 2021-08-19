#!/usr/bin/env python3.8

from dict import site_pass, flag
import random

count = 0


print("Send the recovered password here and I'll check if you are genuine")
tot = random.randint(60,100)
websites = list(site_pass.keys())
for i in range(tot) :
    site = random.choice(websites)
    print("Website : ", site)
    print("Pass length :" , len(site_pass[site]))
    print("Enter the password :")
    pswd = input()
    if pswd == site_pass[site] :
        print("Correct!")
        count += 1
    else :
        print("Incorrect :(")
percentage = (count/tot)*100
print("Your correctness percentage is :" , percentage , "%" )
if(percentage >= 0.75) :
    print("Here is your flag :", flag)
else :
    print("Your need to get at least 75% of the passwords right!")
    print("Better luck next time")
