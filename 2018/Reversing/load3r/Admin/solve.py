
def decrypt():
    str_ = "w2g1kS<c7me3keeuSMg1kSk%Se<=S3%/e/"[::-1]
    const = '0100010011011101111111011010110101'
    xor = ''

    for i in str_:
        xor += chr(ord(i)^5)

    out = ''
    for i in xrange(len(xor)):
        if const[i] == '1':
            out += chr(ord(xor[i])>>1)
        else:
            out += chr(ord(xor[i])<<1)
    print "The flag is: inctf{" + out + "}"

decrypt()
