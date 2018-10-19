#include <unicorn/unicorn.h>
#include <stdio.h>
#include <string.h>

#define ARM_CODE "\x11\x0a\xa0\xe3\x12\x5a\xa0\xe3\x01\xb0\xa0\xe3\x00\x10\xa0\xe3\x01\x20\xd0\xe7\x05\x20\x22\xe2\xff\x20\x02\xe2\x07\x20\x82\xe2\x01\x30\xd5\xe7\xff\x30\x03\xe2\x01\x10\x81\xe2\x03\x00\x52\xe1\x01\x00\x00\x0a\x00\xb0\xa0\xe3\x01\x00\x00\xea\x13\x00\x51\xe3\xf2\xff\xff\xda\x00\xf0\x20\xe3"
#define MIPS_CODE "\x0a\x00\x08\x24\x02\x48\x28\x71\x02\x00\x08\x24\x20\x48\x28\x01\x0a\x00\x08\x24\x02\x50\x48\x71\xfe\x00\x08\x24\x22\x50\x48\x01\x14\x00\x08\x24\x02\x58\x68\x71\x04\x00\x08\x24\x20\x58\x68\x01\x00\x00\x00\x00\x01\x00\x08\x3c\x00\x10\x08\x35\x00\x00\x0c\x81\x01\x00\x08\x25\x72\x00\x09\x24\x20\x00\x89\x15\x00\x00\x00\x00\x00\x00\x0c\x81\x01\x00\x08\x25\x5f\x00\x09\x24\x1b\x00\x89\x15\x00\x00\x00\x00\x00\x00\x0c\x81\x01\x00\x08\x25\x61\x00\x09\x24\x16\x00\x89\x15\x00\x00\x00\x00\x00\x00\x0c\x81\x01\x00\x08\x25\x6e\x00\x09\x24\x11\x00\x89\x15\x00\x00\x00\x00\x00\x00\x0c\x81\x01\x00\x08\x25\x64\x00\x09\x24\x0c\x00\x89\x15\x00\x00\x00\x00\x00\x00\x0c\x81\x01\x00\x08\x25\x5f\x00\x09\x24\x07\x00\x89\x15\x00\x00\x00\x00\x00\x00\x0c\x81\x01\x00\x08\x25\x68\x00\x09\x24\x02\x00\x89\x15\x00\x00\x00\x00\x02\x00\x00\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\xad\x25\x02\x00\xce\x25\x03\x00\xef\x25\x04\x00\x18\x27\x05\x00\x39\x27\x06\x00\x10\x26\x07\x00\x31\x26\x00\x00\x00\x00"

#define ADDRESS 0x10000

static void hook_code_mips(uc_engine *uc, uint64_t address, uint32_t size, void *user_data)
{
    int t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, s0, s1;

    uc_reg_read(uc, UC_MIPS_REG_T0, &t0);
    uc_reg_read(uc, UC_MIPS_REG_T1, &t1);
    uc_reg_read(uc, UC_MIPS_REG_T2, &t2);
    uc_reg_read(uc, UC_MIPS_REG_T3, &t3);
    uc_reg_read(uc, UC_MIPS_REG_T4, &t4);
    uc_reg_read(uc, UC_MIPS_REG_T5, &t5);
    uc_reg_read(uc, UC_MIPS_REG_T6, &t6);
    uc_reg_read(uc, UC_MIPS_REG_T7, &t7);
    uc_reg_read(uc, UC_MIPS_REG_T8, &t8);
    uc_reg_read(uc, UC_MIPS_REG_T9, &t9);
    uc_reg_read(uc, UC_MIPS_REG_S0, &s0);
    uc_reg_read(uc, UC_MIPS_REG_S1, &s1);

    if (address == 0x10010) {
        uc_reg_read(uc, UC_MIPS_REG_T1, &t1);
        if (t1 != 512) {
            printf("Try Again!");
            uc_emu_stop(uc);
            exit(0);
        }
    }
    if (address == 0x10020) {
        uc_reg_read(uc, UC_MIPS_REG_T2, &t2);
        if (t2 != 256) {
            printf("Try Again!");
            uc_emu_stop(uc);
            exit(0);
        }
    }
    if (address == 0x10030) {
        uc_reg_read(uc, UC_MIPS_REG_T3, &t3);
        if (t3 != 1024) {
            printf("Try Again!");
            uc_emu_stop(uc);
            exit(0);
        }
    }
    if (address == 0x100d0) {
        printf("\nYou can do better!");
        uc_emu_stop(uc);
        exit(0);
    }
}

int check1(char input1[]) {
    uc_engine *uc;
    uc_err err;
    uc_hook trace1;
    int r11;

    char str[20] = "xt=aok}x=~as}a~<<xw}";

    if ((strlen(input1) * 2) + 10 != 50) {
        printf("\nInvalid Length");
        exit(0);
    }

    err = uc_open(UC_ARCH_ARM, UC_MODE_ARM, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n", err, uc_strerror(err));
        return 0;
    }

    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);
    uc_mem_write(uc, ADDRESS, ARM_CODE, sizeof(ARM_CODE) - 1);
    uc_mem_write(uc, ADDRESS + 0x1000, input1, strlen(input1));
    uc_mem_write(uc, ADDRESS + 0x2000, str, strlen(str));

    err = uc_emu_start(uc, ADDRESS, ADDRESS + 0x44, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u(%s)\n", err, uc_strerror(err));
        return 0;
    }

    uc_reg_read(uc, UC_ARM_REG_R11, &r11);

    uc_close(uc);
    return r11;
}


int check2(char input2[]) {
    uc_engine *uc;
    uc_err err;
    uc_hook trace1;
    int t1 = input2[0];
    int t2 = input2[8];
    int t3 = input2[13];
    char mid1[7], mid2[7], last[8];

    if ((strlen(input2) * 2) + 2 != 50) {
        printf("\nInvalid Length or Input");
        return 0;
    }

    strcpy(last, &input2[16]);
    strncpy(mid1, &input2[1], 7);
    strncpy(mid2, &input2[9], 7);

    if (strcmp(last, "un1c0rn!") != 0) {
        return 0;
    }

    err = uc_open(UC_ARCH_MIPS, UC_MODE_MIPS32 + UC_MODE_LITTLE_ENDIAN, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n", err, uc_strerror(err));
        return 0;
    }

    int t5, t6, t7, t8, t9, s0, s1;
    t5 = mid2[0];
    t6 = mid2[1];
    t7 = mid2[2];
    t8 = mid2[3];
    t9 = mid2[4];
    s0 = mid2[5];
    s1 = mid2[6];

    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);
    uc_mem_write(uc, ADDRESS, MIPS_CODE, sizeof(MIPS_CODE) - 1);
    uc_mem_write(uc, ADDRESS + 0x1000, mid1, strlen(mid1));

    uc_reg_write(uc, UC_MIPS_REG_T1, &t1);
    uc_reg_write(uc, UC_MIPS_REG_T2, &t2);
    uc_reg_write(uc, UC_MIPS_REG_T3, &t3);
    uc_reg_write(uc, UC_MIPS_REG_T5, &t5);
    uc_reg_write(uc, UC_MIPS_REG_T6, &t6);
    uc_reg_write(uc, UC_MIPS_REG_T7, &t7);
    uc_reg_write(uc, UC_MIPS_REG_T8, &t8);
    uc_reg_write(uc, UC_MIPS_REG_T9, &t9);
    uc_reg_write(uc, UC_MIPS_REG_S0, &s0);
    uc_reg_write(uc, UC_MIPS_REG_S1, &s1);

    uc_hook_add(uc, &trace1, UC_HOOK_CODE, hook_code_mips, NULL, 1, 0);

    err = uc_emu_start(uc, ADDRESS, ADDRESS + sizeof(MIPS_CODE) - 1, 0, 0);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u(%s)\n", err, uc_strerror(err));
        return 0;
    }

    uc_reg_read(uc, UC_MIPS_REG_T5, &t5);
    uc_reg_read(uc, UC_MIPS_REG_T6, &t6);
    uc_reg_read(uc, UC_MIPS_REG_T7, &t7);
    uc_reg_read(uc, UC_MIPS_REG_T8, &t8);
    uc_reg_read(uc, UC_MIPS_REG_T9, &t9);
    uc_reg_read(uc, UC_MIPS_REG_S0, &s0);
    uc_reg_read(uc, UC_MIPS_REG_S1, &s1);

    if (t5 != 96 || t6 != 110 || t7 != 51 || t8 != 122 || t9 != 56 || s0 != 121 || s1 != 102) {
        uc_close(uc);
        return 0;
    }

    uc_close(uc);
    return 1;
}

void printflag(char input1[], char input2[]) {
    printf("-------------------\n");
    printf("The FLAG is: inctf{%s%s}\n", input1, input2 );
}

void main() {
    char input1[20], input2[23];

    int ch1, ch2;
    printf("----_-Stage 1-_----\n");
    printf("Enter input: ");
    scanf("%s", input1);
    ch1 = check1(input1);
    if (ch1 == 0) {
        printf("\nNope!");
    }
    else {
        printf("\nStage 1 completed!\n");
        printf("\n----_-Stage 2-_----\n");
        printf("Enter input: ");
        scanf("%s", input2);
        ch2 = check2(input2);

        if (ch2 == 1) {
            printf("\nStage 2 completed!\n");
            printf("\nGood Work!!\n");
            printflag(input1, input2);
        }
        else {
            printf("\nTry harder... :)");
        }

    }

}
