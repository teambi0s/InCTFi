import ecc
import sys
import os
from prng import prng
from flag import flag

class colors:
    reset='\033[0m'
    red='\033[31m'
    green='\033[32m'
    orange='\033[33m'
    blue='\033[34m'

# New urandom seed for each session (Not really relevant for the challenge)
prng_obj = prng(16793527392756720769, 2358102439659339126076356431940385122127543421625845446663, False)

p = 2**256 - 2**224 + 2**192 + 2**96 - 1
a = p-3
b = 41058363725152142129326129780047268409114441015993725554835256314039467401291
ec = ecc.CurveFp(p, a, b)

_Px = 53881495764268889303293517690095107010093794097958309592680107528631746121613
_Py = 69534606358473748292927094386662082099432383517498778127513290350658945146669
Point_P = ecc.Point(ec, _Px, _Py)

iteration = True
counter = 0

while iteration == True and counter < 10:
    print colors.blue + "Choose one between authentication protocols listed below:" + colors.reset
    print colors.orange + "[1] Asynchronous SchnorrID" + colors.reset
    print colors.orange + "[2] Synchronous SchnorrID" + colors.reset
    choice = int(raw_input("Enter your choice: "))
    print ""

    if choice == 1:
        print "Here are the coordinates of the base point P: ", _Px, _Py
        _Qx, _Qy = map(int, raw_input(colors.orange + "Enter coordinates of point Q: " + colors.reset).split(":"))
        _Rx, _Ry = map(int, raw_input(colors.orange + "Enter coordinates of point R: " + colors.reset).split(":"))
        assert _Qx != 0 and _Qy != 0 and _Rx != 0 and _Ry != 0
        Point_Q = ecc.Point(ec, _Qx, _Qy)
        Point_R = ecc.Point(ec, _Rx, _Ry)

        e = prng_obj.prng_generate()
        print ""
        print colors.blue + "Here, take e: ", colors.reset + str(e)
        print ""

        s = int(raw_input("Compute and give me s: "))
        assert s != 0
        res = e*Point_Q + Point_R

        if (s*Point_P).x() == res.x() and (s*Point_P).y() == res.y():
            flag_bit = 0
            print ""
            print colors.green + "Authentication Successfull!" + colors.reset
            print ""
        else:
            flag_bit = 0
            print ""
            print colors.red + "Authentication Failed!" + colors.reset
            sys.exit(0)

    elif choice == 2:
        print "Here are the coordinates of the base point P: ", _Px, _Py
        _Qx, _Qy = map(int, raw_input(colors.orange + "Enter coordinates of point Q: " + colors.reset).split(":"))
        _Rx, _Ry = map(int, raw_input(colors.orange + "Enter coordinates of point R: " + colors.reset).split(":"))
        assert _Qx != 0 and _Qy != 0 and _Rx != 0 and _Ry != 0
        Point_Q = ecc.Point(ec, _Qx, _Qy)
        Point_R = ecc.Point(ec, _Rx, _Ry)

        e = prng_obj.prng_generate()
        print ""
        s = int(raw_input(colors.orange + "Compute and give me s: " + colors.reset))
        assert s != 0
        res = e*Point_Q + Point_R

        if (s*Point_P).x() == res.x() and (s*Point_P).y() == res.y():
            flag_bit = 1
            print ""
            print colors.green + "Authentication Successfull!" + colors.reset
            print ""
        else:
            flag_bit = 0
            print ""
            print colors.red + "Authentication Failed!" + colors.reset
            sys.exit(0)
    else:
        print colors.red + "Please enter a valid choice!" + colors.reset
        sys.exit(0)

    iteration = False
    counter += 1

    print colors.blue + "Select an option:" + colors.reset
    print colors.orange + "[1] Read flag" + colors.reset
    print colors.orange + "[2] Close connection" + colors.reset
    print colors.orange + "[3] Close session" + colors.reset
    choice = int(raw_input("Enter your choice: "))
    if choice == 1:
        if flag_bit == 1:
            print ""
            print colors.green + "Here, take your flag: " + colors.reset + flag
        else:
            print ""
            print colors.red + "Cannot read flag! Permission Denied!" + colors.reset
            sys.exit(0)
    elif choice == 2:
        iteration = True
    elif choice == 3:
        sys.exit(0)
