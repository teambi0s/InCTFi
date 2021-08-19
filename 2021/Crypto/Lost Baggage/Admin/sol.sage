from Crypto.Util.number import long_to_bytes as l2b
import pickle

val = pickle.load(open('enc.pickle', 'rb'))

def atk(val, nbit):
	A = Matrix(ZZ, nbit+1,nbit+1)
	for i in range(nbit):
		A[i,i] = 2
		A[i,nbit] = val['pbkey'][i]
		A[nbit,i] = 1
	A[nbit,nbit] = val['cip']
	return A.LLL()

nbit = len(val['pbkey'])
res = atk(val, nbit)
for i in range(nbit):
	if all([j in range(-2, 2) for j in res[i][1:-1]]):
		print(res[i])
		msg = int(''.join(['1' if i<=-1 else '0' for i in res[i][:-1][::-1]]), 2)
		print(l2b(msg))