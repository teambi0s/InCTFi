import hashlib, pickle
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
from tqdm import trange

val = pickle.load(open('enc.pickle', 'rb'))

def decrypt(msg, iv, key):
	key = hashlib.sha256(str(key).encode()).digest()[:16]
	cipher = AES.new(key, AES.MODE_CBC, iv)
	try:
		out = unpad(cipher.decrypt(msg), 16)
		assert b'inctf{' in out
		return  out
	except:
		return False

def main(EC, val):
	G = EC.gens()[0]
	cip = bytes.fromhex(val['cip'])
	iv = bytes.fromhex(val['iv'])
	for i in trange(420462, 1040400):
		P = i*G
		ret = decrypt(cip, iv, P.xy()[0])
		if ret!=False:
			return ret

if __name__ == '__main__':
	p = 0xFFFFFFFF00000001000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFF
	a = p - 3
	b = 0x5AC635D8AA3A93E7B3EBBD55769886BC651D06B0CC53B0F63BCE3C3E27D2604B
	EC = EllipticCurve(GF(p), [a, b])
	print(main(EC, val))