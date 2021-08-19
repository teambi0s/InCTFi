#! /usr/bin/python3
import random
from string import ascii_lowercase as all_letters
import os

#to generate puzzle
def generate_puzzle(num):
    mat=[[[0 for _ in range(num)] for _ in range(num)] for _ in range(2)]
    letters=[]
    for i in range(num):
        while True:
            letter=random.choice(all_letters)
            if letter not in letters:
                break
        letters.append(letter)
        for puzz in mat:
            while True:
                l1=random.randint(0,num-1)
                l2=random.randint(0,num-1)
                if mat[1][l1][l2]==0 and mat[0][l1][l2]==0:
                    puzz[l1][l2]=letter
                    break 
    return mat[0],mat[1]

#prints array 
def print_arr(arr):
    [print("+"+"-"*(len(arr[0])*4-1)+"+", end=" "*len(arr[0])) for j in arr]
    for i in range(len(arr[0])):
        print()
        for k in arr:
            for j in range(len(arr[0])):
                if(j==0):
                    print("|", k[i][j], end='')
                else:
                    print(" |",k[i][j],end='')
            print(" |", end=" "*len(arr[0]))
    print()
    [print("+"+"-"*(len(j[i])*4-1)+"+", end=" "*len(arr[0])) for j in arr]
    print()


#checks the validity of the movement
def check(a,b,c,d):
    if(abs(a-c)>=1 and abs(b-d)>=1):
        return False
    return True

def find_index(arr):
    ret={}
    for i in range(len(arr)):
        for j in range(len(arr)):
            if '0' != arr[i][j] and 0!=arr[i][j]:
                ret[arr[i][j]]=[i,j]
    return ret

def find_moves(lev,sol):
    lev_index = find_index(lev)
    sol_index = find_index(sol)
    needed=0
    for i in lev_index.keys():
        needed += abs(lev_index[i][0]-sol_index[i][0])+abs(lev_index[i][1]-sol_index[i][1])
    return needed

if __name__=='__main__':
    print('''Welcome to Alpha pie game!!!
Rules:
1. To complete one level you have match the left matrix to the right one by moiving each letter to their position in the right matrix
2. Moving to only adjecent column or row is possible.
3. Diagonal movements are not possible
4. negative numbers are not allowed in the input
5. The input format should be 'current-x-cord,current-y-cord,to-x-cord,to-y-cord'.
   eg : 0,0,0,1 (Will move letter at position 0,0 to position 0,1 if a letters is present at 0,0 and no letter is present at 0,1).
7. Number of moves will be limited for each level.
8. The game has a time limit of 'n' minutes.
9. You will lose the game if you enter certain number of invalid moves
10. After you pass 9 levels you will ge the flag.
   Good luck ! Enjoy the game 👍''')
    if input("\nPress 'y' to start: ")=='y':
        pass
    else:
        print("Bye Bye")
        exit()
    for i in range(2,11):
        print(f"Level-{i-1}")
        lev,sol=generate_puzzle(i)
        mov=0
        invalid=0
        needed=find_moves(lev,sol)+i-1
        print("Max number of moves allowed:",needed)
        while True:
            print_arr([lev,sol])
            print("Current moves :",mov)
            a,b,c,d=map(int,input("Enter move in the format \'current-x-cord,current-y-cord,to-x-cord,to-y-cord \' : ").split(','))
            if a<0 or b<0 or c<0 or d<0 :
                print("Enter positive co-ordinates :(")
                continue
            try:
                if lev[a][b] == 0 or lev[c][d] != 0:
                    invalid+=1
                    if invalid>=needed//2:
                        print("You have lost :(")
                        exit()
                    print("Enter valid position :(")
                    continue
                if check(a,b,c,d):
                    lev[a][b],lev[c][d] = lev[c][d],lev[a][b]
                else:
                    print("Invalid Movement")
                    invalid+=1
                    if invalid>=needed//2:
                        print("You have lost :(")
                        exit()
                    continue
                mov+=1
                if lev==sol:
                        print(f"Congrats Level Completed in {mov} moves :)")
                        break
                if mov >= needed or invalid>=needed//2  :
                    print("You have lost :(")
                    exit()

            except Exception as e:
                print("Invalid :(")
                invalid+=1
                continue
    print(os.getenv('FLAG'))
