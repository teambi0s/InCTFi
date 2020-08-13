package main

import (
	"bytes"
	"errors"
	"fmt"
	"reflect"
	"strconv"
	"strings"
	"syscall"
)

type var1 struct {
	var2      int
	var3    string
	var4 uint64
	var5       []byte
}

var test int = 1
var var6 int = 1
var var7 []var1
var names = []string{"R15", "R14", "R13", "R12", "Rbp", "Rbx", "R11", "R10", "R9", "R8", "Rax", "Rcx", "Rdx", "Rsi", "Rdi", "Orig_rax", "Rip", "Cs", "Eflags", "Rsp", "Ss", "Fs_base", "Gs_base", "Ds", "Es", "Fs", "Gs"}
var var8 []uint64

func check1(arg1 *var1) {
	fmt.Println((*arg1).var2)
	fmt.Println((*arg1).var3)
	fmt.Println((*arg1).var4)
	fmt.Println((*arg1).var5)
}

func check2(arg1 int, arg2 string) error {
	lvar1, err := func1(arg2)
	if err != nil {
		return err
	}
	lvar2, err := check4(arg1, lvar1, []byte{0xCC})
	if err != nil {
		return err
	}
	var7 = append(var7, var1{var6, arg2, lvar1, lvar2})
	var8 = append(var8, lvar1)
	var6 = var6 + 1
	//fmt.Printf("[-] Breakpoint set at %x\n", lvar1)
	return nil
}

func check3(arg1 int, arg2 string) error {
	arg2 = strings.TrimPrefix(arg2, "0x")
	lvar1, err := strconv.ParseUint(arg2, 16, 64)
	lvar2, err := check4(arg1, lvar1, []byte{0xCC})
	if err != nil {
		return err
	}
	var7 = append(var7, var1{var6, "Unknown", lvar1, lvar2})
	var8 = append(var8, lvar1)
	var6 = var6 + 1
	//fmt.Printf("[-] Breakpoint set at %x\n", lvar1)
	return nil
}

func check4(arg1 int, arg2 uint64, arg3 []byte) ([]byte, error) {
	lvar1 := make([]byte, len(arg3))
	_, err := syscall.PtracePeekData(arg1, uintptr(arg2), lvar1)
	// fmt.Println(arg1, arg2, lvar1, arg3)
	if err != nil {
		//return nil, errors.New("Unable to peek")
		return nil, err
	}
	_, err = syscall.PtracePokeData(arg1, uintptr(arg2), arg3)
	if err != nil {
		return nil, errors.New("Unable to poke")
	}
	return lvar1, nil
}

func check5(arg1 int, arg2 string) (int64, error) {
	lvar1, err := func2(arg2)
	if err != nil {
		return 0, err
	}
	return check7(arg1, int64(lvar1), 1)
}

func check6(arg1 int, arg2 string) (int64, error) {
	arg2 = strings.TrimPrefix(arg2, "0x")
	lvar1, err := strconv.ParseInt(arg2, 16, 64)
	if err != nil {
		return 0, errors.New("Could not parse pointer")
	}
	return check7(arg1, lvar1, 1)
}

func check7(arg1 int, arg2 int64, arg3 int64) (int64, error) {
	lvar1 := make([]byte, arg3*4)
	for i := int64(0); i < arg3; i++ {
		lvar2, err := syscall.PtracePeekData(arg1, uintptr(arg2+(i*4)), lvar1[i*4:])
		if err != nil {
			return 0, errors.New("Unable to peek")
		}
		if lvar2 == 0 {
			break
		}
		//fmt.Printf("[%x]: %x %x %x %x\n", uintptr(arg2+(i*4)), lvar1[i*4], lvar1[i*4+1], lvar1[i*4+2], lvar1[i*4+3])
	}
	result := int64(int64(lvar1[0]) + int64(lvar1[1])<<8 + int64(lvar1[2])<<16 + int64(lvar1[3])<<24)
	return result, nil
}

func check8(arg1 int) int {
	lvar1, err := check23(arg1, "Rip")
	assert(err)

	for _, lvar2 := range var8 {
		if lvar2 == lvar1-1 {
			lvar3, err := check10(lvar2)
			assert(err)

			//fmt.Println(lvar3.var3)
			return lvar3.var2
		}
	}
	return -1
}

func check9(arg1 int, arg2 uint64) {
	for _, lvar1 := range var7 {
		if lvar1.var4 == arg2 {
			lvar2 := lvar1
			check15(arg1, &lvar2)
			check17(arg1)
			check13(arg1, &lvar2)
		}
	}
}

func check10(arg1 uint64) (*var1, error) {
	for _, lvar1 := range var7 {
		if lvar1.var4 == arg1 {
			return &lvar1, nil
		}
	}
	return nil, errors.New("Breakpoint not found")
}

func check11(arg1 int, arg2 int) {
	for lvar1, lvar2 := range var7 {
		if lvar2.var2 == arg2 {
			check4(arg1, lvar2.var4, lvar2.var5)
			copy(var7[lvar1:], var7[lvar1+1:])
			var7 = var7[:len(var7)-1]
			for lvar3, lvar4 := range var8 {
				if lvar4 == lvar2.var4 {
					copy(var8[lvar3:], var8[lvar3+1:])
					var8 = var8[:len(var8)-1]
				}
			}
			return
		}
	}
	//fmt.Printf("[-] Breakpoint Number %d not found!", arg2)
}

func check12(arg1 int) {
	if len(var7) == 0 {
		fmt.Println("[-] No Breakpoints set!")
		return
	}
	//fmt.Printf("Id\tAddress\tName\n")
	//for _, lvar1 := range var7 {
		//fmt.Printf("%d\t%x\t%s\n", lvar1.var2, lvar1.var4, lvar1.var3)
	//}
}

func check13(arg1 int, arg2 *var1) error {
	lvar1, err := check4(arg1, (*arg2).var4, []byte{0xCC})
	if err != nil {
		return err
	}
	if !bytes.Equal(lvar1, []byte{0xCC}) {
		if !bytes.Equal(lvar1, (*arg2).var5) {
			// TODO: - Good place to keep a amazing flag
			// Keep a check such that the code is modified in running
			(*arg2).var5[0] = lvar1[0]
			test = test | 0xff00
		}
	}
	return nil
}

func check14() int {
	return test
}

func check15(arg1 int, arg2 *var1) error {
	lvar1, err := check4(arg1, (*arg2).var4, (*arg2).var5)
	if err != nil {
		return err
	}
	if !bytes.Equal(lvar1, []byte{0xCC}) {
		test = test | 0xff
	}
	return nil
}

func check16(arg1 int) {
	// Get the value of RIP register
	lvar1, err := check23(arg1, "Rip")
	assert(err)
	// For breakpoint in
	for _, lvar2 := range var8 {
		// if current lvar2 is breakpoint lvar2 + 1
		// That means we are currently in a breakpoint
		// This means that for the continue we need to singlestep the breakpoint
		if lvar2 == lvar1-1 {
			// get the current breakpoint
			check24(arg1, "Rip", lvar1-1)
			lvar3, err := check10(lvar2)
			// disable the current breakpoint
			err = check15(arg1, lvar3)
			assert(err)
			// single step
			lvar4, _ := syscall.Getpgid(arg1)
			assert(syscall.PtraceSingleStep(arg1))
			if waitForSignal(arg1, lvar4) == 1 {
				// Enable a breakpoint
				//fmt.Println("currently continuing from a bp")
				err = check13(arg1, lvar3)
				assert(err)
				break
			} else {
				//fmt.Println("Something fucked up")
			}
		}
	}
	assert(syscall.PtraceCont(arg1, 0))
}

func check17(arg1 int) {
	//fmt.Println("Stepping")
	lvar1, err := check23(arg1, "Rip")
	assert(err)

	for _, lvar2 := range var8 {
		if lvar2 == lvar1-1 {
			check24(arg1, "Rip", lvar2)

			lvar3, err := check10(lvar2)
			// disable the current breakpoint
			err = check15(arg1, lvar3)
			assert(err)
		}
	}
	assert(syscall.PtraceSingleStep(arg1))
}

//func check18(arg1 int) {
//	lvar1 := check19(arg1)
//	fmt.Printf("[*] Stopped at %x\n", lvar1.Rip)
//}

func check19(arg1 int) syscall.PtraceRegs {
	var lvar1 syscall.PtraceRegs
	syscall.PtraceGetRegs(arg1, &lvar1)
	return lvar1
}

func check20(arg1 int) {
	lvar1 := check19(arg1)
	fmt.Printf("RAX : 0x%x\tRBX : 0x%x\tRCX : 0x%x\tRDX : 0x%x\n", lvar1.Rax, lvar1.Rbx, lvar1.Rcx, lvar1.Rdx)
	fmt.Printf("RSI : 0x%x\tRDI : 0x%x\tR8 : 0x%x\tR9 : 0x%x\n", lvar1.Rsi, lvar1.Rdi, lvar1.R8, lvar1.R9)
	fmt.Printf("R10 : 0x%x\tR11 : 0x%x\tR12 : 0x%x\tR13 : 0x%x\n", lvar1.R10, lvar1.R11, lvar1.R12, lvar1.R13)
	fmt.Printf("RIP : 0x%x\tRBP : 0x%x\tRSP : 0x%x\tEFLAGS : 0x%x\n", lvar1.Rip, lvar1.Rbp, lvar1.Rsp, lvar1.Eflags)
}

func check21(arg1 *syscall.PtraceRegs, arg2 string) uint64 {
	r := reflect.ValueOf(arg1)
	f := reflect.Indirect(r).FieldByName(arg2)
	return f.Uint()
}

func check22(arg1 *syscall.PtraceRegs, arg2 string, arg3 interface{}) error {
	lvar1 := reflect.ValueOf(arg1).Elem()
	lvar2 := lvar1.FieldByName(arg2)

	if !lvar2.IsValid() {
		return fmt.Errorf("No such field")
	}

	if !lvar2.CanSet() {
		return fmt.Errorf("Cannot set field")
	}

	lvar3 := lvar2.Type()
	val := reflect.ValueOf(arg3)
	if lvar3 != val.Type() {
		return errors.New("Provided arg3 type didn't match field type")
	}

	lvar2.Set(val)
	return nil
}

func check23(arg1 int, arg2 string) (uint64, error) {
	arg2 = strings.TrimSpace(arg2)
	_, lvar1 := Find(names, arg2)
	if !lvar1 {
		return 0, errors.New("Illegal Register")
	}
	regs := check19(arg1)
	return check21(&regs, arg2), nil
}

func check24(arg1 int, arg2 string, arg3 uint64) error {
	arg2 = strings.TrimSpace(arg2)
	_, lvar1 := Find(names, arg2)
	if !lvar1 {
		return errors.New("Illegal Register")
	}
	lvar2 := check19(arg1)
	check22(&lvar2, arg2, arg3)
	return syscall.PtraceSetRegs(arg1, &lvar2)
}

func check25(arg1 int, arg2 string) {
	lvar1, err := check23(arg1, arg2)
	if err != nil {
		fmt.Println(arg2 + " isn't a valid register")
		return
	}
	fmt.Printf("%s : 0x%x\n", arg2, lvar1)
}
