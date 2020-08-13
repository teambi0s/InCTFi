package main

import (
	"debug/elf"
	"fmt"
	"os"
	"syscall"
	"time"
)

type svar1 struct {
	Name   string
	Offset uint64
}

type svar4 struct {
	// Contains all the symbols the binary looks for
	svar5 elf.FileHeader
	svar6  []svar1
	svar7   []svar1
	svar8  []svar1
}

func func3(arg1 string) *svar4 {
	lvar1, err := elf.Open(arg1)
	if err != nil {
		fmt.Println("WTF?")
		os.Exit(1)
	}
	defer lvar1.Close()

	lvar2 := svar4{}

	lvar2.svar5 = lvar1.FileHeader

	lvar3, _ := lvar1.Symbols()
	for _, lvar4 := range lvar3 {
		// All svar6 have symbols as 18
		if lvar4.Info == 18 {
			lvar2.svar6 = append(lvar2.svar6, svar1{lvar4.Name, lvar4.Value})
		} else if lvar4.Info == 17 {
			lvar2.svar8 = append(lvar2.svar8, svar1{lvar4.Name, lvar4.Value})
		} else {
			continue
		}
	}

	for _, lvar5 := range lvar1.Sections {
		lvar2.svar7 = append(lvar2.svar7, svar1{(*lvar5).SectionHeader.Name, (*lvar5).SectionHeader.Addr})
	}

	return &lvar2
}

func func4(arg1 *svar4, arg2 int) {
	if (*arg1).svar5.Class != 2 {
		time.AfterFunc(1*time.Second, func() { syscall.Kill(arg2, syscall.SIGSEGV) })
	}
	if (*arg1).svar5.Type == 3 {
		time.AfterFunc(1*time.Second, func() { syscall.Kill(arg2, syscall.SIGSEGV) })
	}
}
