import random
import time

random.seed(time.time())

s = '''mov cnt r2 {}
chk lt r1 r2
jmp chk 4095'''
s2 = '''mov cnt r2 {}
chk gt r1 r2
jmp chk 4095'''

flag = "inctf{1_kN0w_1t5_R3411y_3z_&_fuNNy_but_1ts_h0n3st_w0rk!}"
for letter in flag:
    k = random.randrange(13,29)
    f_loc = random.randrange(0,123) % k
    f_loc2 = random.randrange(0,123) % k
    print "in r1"
    if(f_loc == f_loc2):
        f_loc = f_loc + 1
    for i in range(k+1):
        if(i==f_loc):
            print s.format(ord(letter))
        elif(i==f_loc2):
            print s2.format(ord(letter))
        elif(random.choice([0,1])):
            print s.format(random.randrange(0,ord(letter)-1))
        else:
            print s2.format(random.randrange(ord(letter)+1,254))
