#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

enum
{
    R_IP,
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_FLAG,
    R_FIN,      
    R_COUNT
};
int reg[R_COUNT];

enum
{
    OP_STR,
    OP_LD,
    OP_IN,
    OP_OUT,    /* prvoid */
    OP_MOV,
    OP_CHK,    /* chk */ 
    OP_XOR,    /* xor */
    OP_MUL,
    OP_SHL,
    OP_SHR,
    OP_ADD,    /* add  */
    OP_HLT,
    OP_JMP,
    OP_CHKFLG,
    OP_IMOD,
    OP_COUNT
};
int flag = 0;

#define MEM_MAX 2048
#define IMEM_MAX 100000

int mem[MEM_MAX];
u_int64_t imem[IMEM_MAX];
int instr_max;
u_int64_t cur_instr;
int total_size;

enum 
{
    OP_SINGLE,
    OP_DOUBLE,
    OP_TRIPLE,
    OP_TYPE_COUNT
};

struct opcode_handler {
    int op_type;
    int op;
    int reg1;
    int reg2;
    int reg3;
    int constant;
    int shift;
    int address;
    int mode;
}op;

static void retrieve_opcode(u_int64_t);
static int handle_single();
static int handle_double();
static int handle_triple();
static int handle_store();
static int handle_load();
static void handle_error();
static void handle_default(int);
static int handle_add();
static int handle_imod();
static int handle_jmp();
static int handle_mul();
static int handle_shl();
static int handle_shr();
static int handle_xor();
static int handle_chk();
static int handle_in();
static int handle_out();
static int handle_hlt();
static int handle_mov();
static int handle_check_flag();
static int parse_file(FILE *);
static u_int64_t mem_read();
static void setup_vm();


int main(int argc, const char* argv[])
{
    FILE * fp;
    struct opcode_handler * oph;
    if (argc < 2) {
        printf("Incorrect usage\n");
        exit(0);
    }
    size_t len1 = strlen(argv[1]);
    if (argv[1][len1 - 1] != 'i' || argv[1][len1 - 2] != '.') {
        printf("Wrong file type\n");
        exit(-2);
    }
    fp = fopen(argv[1],"rb");
    char * line = NULL;
    size_t len = 10;
    
    if (!parse_file(fp)) {
        printf("[*] File format not proper\n");
        exit(-1);
    }

    setup_vm();

    while (1) {
        u_int64_t instr = mem_read(line);
        if (instr == 0) {
            handle_default(instr);
        }
        if(reg[R_FIN] != 0) {
            printf("Incorrect\n");
            break;
        }
        int ret;
        retrieve_opcode(instr);
        switch(op.op_type) {
            case OP_SINGLE:
                ret = handle_single();
                break;
            case OP_DOUBLE:
                ret = handle_double();
                break;
            case OP_TRIPLE:
                ret = handle_triple();
                break;
            default:
                handle_error();
                break;
        }
        if (ret == 0) {
            printf("Return val 0");
		handle_error();
        }
        reg[R_IP] = reg[R_IP] + 1;
    }
    fclose(fp);
}

static int check_regs(int num) {
    if ( num == 1 && (op.reg1 == R_IP || op.reg1 == R_FLAG || op.reg1 >= R_COUNT))
        return 0;
    if ( num == 2 && (op.reg2 == R_IP || op.reg2 == R_FLAG || op.reg2 >= R_COUNT))
        return 0;    
    if ( num == 3 && (op.reg3 == R_IP || op.reg3 == R_FLAG || op.reg3 >= R_COUNT))
        return 0;
    return 1;
}

static void setup_vm() {
    printf("[*] Setting up\n");
    reg[R_IP] = 0;
    reg[R_FLAG] = 0;
    reg[R_FIN] = 0;
}

static void handle_error() {
    printf("[*] File Format not proper\n");
    exit(-1);
}

static int parse_file(FILE *fp) {
    int header, size, instr;
    if(!fread(&header, sizeof(header), 1, fp)) {
        printf("[*] IO trouble");
    	return 0;
    }
    if(header == 12312312) { //change val here
        handle_error();
    }
    else {
        if(!fread(&size, sizeof(size), 1, fp)) {
            printf("[*] IO trouble");
    	return 0;
        }
		total_size = size;
        if(!fread(&imem, sizeof(u_int64_t), size, fp)) {
            printf("[*] IO trouble\n");
    	return 0;
        }
        instr_max = size;
    }
    return 1;
}

static int handle_check_flag() {
    if(reg[R_R0] != 0) {
        return 0;
    }
    return 1;
}

static int handle_single() {
    int ret;
    switch(op.op) {
        case OP_STR:
            ret = handle_store(); 
            break;
        case OP_LD:
            ret = handle_load();
            break;
        case OP_IN:
            ret = handle_in();
            break;
        case OP_OUT:
            ret = handle_out();
            break;
        case OP_MOV:
            ret = handle_mov();
            break;
        default:
            ret = 0;
    }
    return ret;
}

static int handle_double() {
    int ret;
    switch(op.op) {
        case OP_CHK:
            ret = handle_chk();
            break;
        case OP_XOR:
            ret = handle_xor();
            break;
        case OP_MUL:
            ret = handle_mul();
            break;
        case OP_SHL:
            ret = handle_shl();
            break;
        case OP_SHR:
            ret = handle_shr();
            break;
        default:
            ret = 0;
    }
    return ret;
}

static int handle_triple() {
    int ret;
    switch(op.op) {
        case OP_ADD:
            ret = handle_add();
            break;
        case OP_HLT:
            ret = handle_hlt();
            break;
        case OP_JMP:
            ret = handle_jmp();
            break;
        case OP_CHKFLG:
            ret = handle_check_flag();
            break;
        case OP_IMOD:
            ret = handle_imod();
            break;
        default:
            ret = 0;
    }
    return ret;

}

static int handle_store() {
    if(!check_regs(1)) {
        return 0;
    }
	if (op.mode == 1) {
		if( op.constant >= MEM_MAX ) {
			return 0;
		}
    	mem[op.constant] = reg[op.reg1];
    	return 1;
	}
	else {
		if (op.mode == 2) {
			if(!check_regs(1)) {
				return 0;
			}
			mem[reg[op.reg2]] = reg[op.reg1];
    		return 1;
		}
	}
    return 0;
}

static int handle_mul() {
    if(!check_regs(1) || !check_regs(2) || !check_regs(3)) {
        return 0;
    }
    reg[op.reg1] = reg[op.reg2] * reg[op.reg3];
    return 1;
}

static int handle_shl() {
    if(!check_regs(1)) {
        return 0;
    }
    reg[op.reg1] = reg[op.reg1] << op.constant;
    return 1;
}

static int handle_shr() {
    if(!check_regs(1)) {
        return 0;
    }
    reg[op.reg1] = reg[op.reg1] >> op.constant;
    return 1;
}

static int handle_load() {
    if(!check_regs(1)) {
        return 0;
    }
	if (op.mode == 1) {
		if( op.constant >= MEM_MAX ) {
			return 0;
		}
    	reg[op.reg1] = mem[op.constant];
    	return 1;
	}
	else {
		if (op.mode == 2) {
			if(!check_regs(1)) {
				return 0;
			}
			reg[op.reg1] = mem[reg[op.reg2]];
    		return 1;
		}
	}
    return 0;
}

static int handle_jmp() {
	if(op.address >= IMEM_MAX) {
        return 0;
    }
    if(op.mode == 2) {
        reg[R_IP] = op.address; 
    }
    if(op.mode == 1) {
        if (reg[R_FLAG]) {
            reg[R_IP] = op.address;
            reg[R_FLAG] = 0;
        }   
    }
    if(op.mode == 0) {
        reg[R_IP] = reg[R_IP] + op.constant;
    }
    return 1;
}

static void retrieve_opcode(u_int64_t instr) {
    cur_instr = instr;
    op.address=(instr& 0xfff000000000000) >> 52;
    op.mode = (instr & 0xf000000000000) >> 48;
    op.reg1 = (instr & 0xf00000000000) >> 44;
    op.reg2 = (instr & 0x0f0000000000) >> 40;
    op.reg3 = (instr & 0x00f000000000) >> 36;
    op.op =   (instr & 0x000fff000000) >> 24;
    op.constant =instr&0x000000ffffff;
    op.op_type = op.op / 5;
    return ;
} 

static void handle_default(int op) {
    printf("[*] Error handling OPCODE :%d\n", op);
    exit(-1);
}

static int handle_imod() {
    if(op.address >= IMEM_MAX || !check_regs(1) || !check_regs(2)) {
        return 0;
    }
    if(op.mode == 1) {
        if(op.address + reg[R_IP] >= IMEM_MAX) {
            return 0;
        }
        imem[reg[R_IP] + op.address] = reg[op.reg1];
        imem[reg[R_IP] + op.address] = (u_int64_t)reg[op.reg2] << 32;
    }
    else {
        if(op.mode == 2) {
            if(op.address + reg[R_IP] >= IMEM_MAX) {
                return 0;
            }
            imem[reg[R_IP] + op.address] = (imem[reg[R_IP] + op.address] & ~0x000fff000000) | reg[op.reg1] << 24; 
        }
    }
    return 1;
}


static int handle_add(){
    if ( !check_regs(1) || !check_regs(2) ) {
        return 0;
    }
    reg[op.reg1] = reg[op.reg2] + op.constant;
    return 1;
}

static int handle_xor(){
    if ( !check_regs(1) || !check_regs(2) || !check_regs(3)) {
        return 0;
    }
    reg[op.reg1] = reg[op.reg2] ^ reg[op.reg3];
    return 1;
}

static int handle_chk() {
    if ( !check_regs(1) || !check_regs(2) ) {
        return 0;
    }
    if(op.mode == 0) {
        if (reg[op.reg2] != reg[op.reg1]) {
            reg[R_FLAG] = 1;
        }
    }
    if(op.mode == 1) {
        if (reg[op.reg1] > reg[op.reg2]) {
            reg[R_FLAG] = 1;
        }
    }
    if(op.mode == 2) {
        if (reg[op.reg1] < reg[op.reg2]) {
            reg[R_FLAG] = 1;
        }
    }
    return 1;
}

static int handle_in(){
    if ( !check_regs(1)) {
        return 0;
    }
    reg[op.reg1] = (int)getchar();
    return 1;
}

static int handle_out(){
    if ( !check_regs(1)) {
        return 0;
    }
    printf("%c", reg[op.reg1]);
    return 1;
}

static int handle_mov(){
    if (!check_regs(1)) {
        return 0;
    }
    if (op.mode == 1) {
		if (!check_regs(2)) {
			return 0;
		}
        reg[op.reg1] = reg[op.reg2];
        return 1; 
    }
    else {
        if(op.mode == 0) { 
            reg[op.reg1] = op.constant;
            return 1;
        }
    }   
    return 0;
}

static int handle_hlt() {
    if (reg[R_FIN] == 0) {
        printf("\nCongratz your input was the flag");
        exit(0);
        return 0;
    }
    else {
        printf("\nSomething's wrong");
        exit(-1);
        return 0;
    }
}

static u_int64_t mem_read() {
    if (reg[R_IP] >= IMEM_MAX) {
        printf("[*] Exhausted\n");
        exit(-1);
    }
    u_int64_t instr = imem[reg[R_IP]];
	return instr;
}
