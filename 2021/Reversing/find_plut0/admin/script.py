from z3 import *
v1 = [BitVec('v1[0]', 16),
BitVec("v1[1]", 16),
BitVec("v1[2]", 16),
BitVec("v1[3]", 16),
BitVec("v1[4]", 16),
BitVec("v1[5]", 16),
BitVec("v1[6]", 16),
BitVec("v1[7]", 16),
BitVec("v1[8]", 16),
BitVec("v1[9]", 16),
BitVec("v1[10]", 16),
BitVec("v1[11]", 16),
BitVec("v1[12]", 16),
BitVec("v1[13]", 16),
BitVec("v1[14]", 16),
BitVec("v1[15]", 16),
BitVec("v1[16]", 16),
BitVec("v1[17]", 16),
BitVec("v1[18]", 16),
BitVec("v1[19]", 16),
BitVec("v1[20]", 16),
BitVec("v1[21]", 16)]
ip = [
BitVec("ip[0]", 16),
BitVec("ip[1]", 16),
BitVec("ip[2]", 16),
BitVec("ip[3]", 16),
BitVec("ip[4]", 16),
BitVec("ip[5]", 16),
BitVec("ip[6]", 16),
BitVec("ip[7]", 16),
BitVec("ip[8]", 16),
BitVec("ip[9]", 16),
BitVec("ip[10]", 16),
BitVec("ip[11]", 16),
BitVec("ip[12]", 16),
BitVec("ip[13]", 16),
BitVec("ip[14]", 16),
BitVec("ip[15]", 16),
BitVec("ip[16]", 16),
BitVec("ip[17]", 16),
BitVec("ip[18]", 16),
BitVec("ip[19]", 16),
BitVec("ip[20]", 16),
BitVec("ip[21]", 16),
BitVec("ip[22]", 16),
BitVec("ip[23]", 16),
BitVec("ip[24]", 16),
BitVec("ip[25]", 16),
BitVec("ip[26]", 16),
BitVec("ip[27]", 16),
BitVec("ip[28]", 16),
BitVec("ip[29]", 16),
]
M=[]
strng = "inctf{U_Sur3_m4Te?}";
for i in range(len(strng)):
	M.append(ord(strng[i]))
s = Solver()
s.add(M[0] == (v1[0]^0x32%4)-31) 
s.add(M[1] == ((v1[1] %2 )^v1[0])-29) 

s.add(M[2] == (v1[1] << 0x2) ^407) 
s.add(M[3] == (v1[2]^416)) 
s.add(M[4] ==  (v1[3] ^0x4d)+7)
s.add(M[5] == (v1[5] << 0x2)-1)  
s.add(M[3]==v1[4]+116)
s.add(M[6] ==(v1[6] -6379))
s.add(M[7] ==5 +v1[7]-0x19) 
s.add(M[8] == 0x63 ^ v1[8]) 
s.add(M[9] ==54+(v1[10]^3)-v1[8] )
s.add(M[10] == (114 & 79)^v1[9])  
s.add(M[11]==51 + v1[11])
s.add(M[11] == (v1[12]^ 179)) 
s.add(M[12] == 26^(v1[13]+18)) 
s.add(M[13] == 59+(v1[14]-66)) 
s.add(M[14] == v1[15]-37) 
s.add(M[15] == v1[17]^ 0xe4 +1) 
s.add(M[3] == (v1[16]^416)) 
s.add(M[16] ==( v1[18]& 0x36)+53) 
s.add(M[14]==v1[19]^52)
s.add(M[17] == (v1[20]^253)) 

s.add(M[18] == (v1[20]>>v1[21])^28) 
s.check()
F=[]
w=[]
F=s.model()
for i in range(0,len(F)):
	w.append(F[v1[i]])

k=Solver()
k.add(w[0]==ip[0]-0x32+ip[1]) 
k.add(w[1]==ip[1]-0x64+ip[2])   
k.add(w[2]==4*ip[2])
k.add(w[3]==ip[3]^70)
k.add(w[4]==36-(ip[3]-ip[4]))
k.add(w[5] == ip[5]-(ip[4])^48)
k.add(w[6] == (ip[6] * ip[5]) + 0x63)
k.add(w[7] == ip[6] ^ ip[7])
k.add(w[8] == (ip[7] + 0x2d) ^ ip[8])
k.add(w[9] == (ip[9] &55)-3)
k.add(w[10] == 64+ip[10] - (ip[9]))
k.add(w[11] == ip[11] -38)
k.add(w[12] == ((ip[12] ^ ip[6]) * 4)+16)
k.add(w[13]==ip[13]^84)
k.add(w[5] == ip[21]-(ip[4])^48)
k.add(w[13] == (ip[13]-ip[14])-1)
k.add(w[14] == ip[15])
k.add(w[15] == 3+(ip[16] ^ ip [15])*2)
k.add(w[10]==ip[17]-ip[16]+82)
k.add(w[16] == (ip[19] *4))
k.add(w[16] == ((ip[18] ^ip[19])*6)+54 )
k.add(w[17] == (ip[20] ^ 0x73) + (ip[21] + 0x31))
k.add(w[14]==ip[22])
k.add(w[18] == (ip[23] << 1)^(161+ip[24]))
k.add(w[18]==ip[23]^66)
k.add(w[15]==ip[26]+5)
k.add(w[19] == ip[25] -(ip[26]/2)-55)
k.add(w[20] == (ip[27] ^ ip[28])+173)
k.add(w[20]==(ip[27] << 2)-(ip[28]+128))
k.add(w[21] == (ip[29]-32))
k.check()
flag=[]
Q=k.model()
for i in range(0,len(Q)):
	flag.append(chr(Q[ip[i]].as_long()))
print("Flag:",''.join(flag))
