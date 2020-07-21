import struct
import sys
import os

def main():
    f = open(sys.argv[1], 'r')
    data = f.readlines()
    wf = open("fin.i", 'w')
    wf.write(struct.pack('=I',0x73306962))
    wf.write(struct.pack('=I',len(data)))
    for sline in data:
        if sline[0] == "#":
            continue
        line = sline.strip().split(' ')
        code = {"str", "ld", "in", "out", "mov", "chk", "xor", "mul", "shl", "shr", "add", "hlt", "jmp", "chkflag", "imod"}
        op = {"str":0, "ld":1, "in":2, "out":3, "mov":4, "chk":5, "xor":6, "mul":7, "shl":8, "shr":9, "add":10, "hlt":11, "jmp":12, "chkflag":13, "imod":14}
        regs = {"ip":0,"r0":1,"r1":2, "r2":3, "r3":4, "r4":5, "r5":6, "r6":7, "r7":8, "flg":9, "fin":10}
        #p1 = fun[code.index(line[0])](line) << 24
	p2 = 0
	p3 = 0
	p4 = 0
	p5 = 0	
        p1 = op[line[0]] << 24
        if line[0] in ["xor", "mul"]:
            p2 = regs[line[1]] << 44
            p3 = regs[line[2]] << 40
            p4 = regs[line[3]] << 36
            wf.write(struct.pack('=Q', p1 + p2 + p3 + p4))
        elif line[0] in ["str", "ld"]:
            if line[1] in ["reg"]:
                p4 = 2 << 48
                p2 = regs[line[2]] << 44
                p3 = regs[line[3]] << 40
            if line[1] in ["addr"]:
                p4 = 1 << 48
                p2 = regs[line[2]] << 44
                p3 = int(line[3])
            wf.write(struct.pack('=Q', p1 + p2 + p3 + p4))
        elif line[0] in ["shl", "shr"]:
            p2 = regs[line[1]] << 44
            p3 = int(line[2])
            wf.write(struct.pack('=Q', p1 + p2 + p3))
        elif line[0] in ["chk"]:
            p2 = regs[line[2]] << 44
            p3 = regs[line[3]] << 40
	    if line[1] in ["gt"]:
		p4 = 1 << 48
	    elif line[1] in ["lt"]:
		p4 = 2 << 48
            elif line[1] in ["eq"]:
		p4 = 0
            wf.write(struct.pack('=Q', p1 + p2 + p3 + p4))
        elif line[0] in ["in", "out"]:
            p2 = regs[line[1]] << 44
            wf.write(struct.pack('=Q', p1 + p2))
        elif line[0] in ["imod"]:
            if line[1] in ["set"]:
                p2 = 1 << 48
            if line[1] in ["mod"]:
                p2 = 2 << 48
            p3 = int(line[2]) << 52
            p4 = regs[line[3]] << 44
            p5 = regs[line[4]] << 40
            wf.write(struct.pack('=Q', p1 + p2 + p3 + p4 + p5))
        elif line[0] in ["jmp"]:
            if line[1] in ["set"]:
                p2 = 2 << 48
                p3 = int(line[2]) << 52
            if line[1] in ["chk"]:
                p2 = 1 << 48
                p3 = int(line[2]) << 52
            if line[1] in ["ip"]:
                p2 = 0 << 48
                p3 = int(line[2])
            wf.write(struct.pack('=Q', p1 + p2 + p3))
        elif line[0] in ["add"]:
            p2 = regs[line[1]] << 44
            p3 = regs[line[2]] << 40
            p4 = int(line[3])
            wf.write(struct.pack('=Q', p1 + p2 + p3 + p4))
        elif line[0] in ["hlt", "chkflag"]:
            wf.write(struct.pack('=Q', p1))
        elif line[0] in ["mov"]:
            if line[1] in ["reg"]:
				p2 = regs[line[2]] << 44
				p3 = regs[line[3]] << 40
				p4 = 1 << 48
	    if line[1] in ["cnt"]:
	    		p2 = regs[line[2]] << 44
              		p3 = int(line[3])
			p4 = 0
            wf.write(struct.pack('=Q', p1 + p2 + p3 + p4))
    wf.close()
    f.close()

if __name__ == "__main__":
    main()
