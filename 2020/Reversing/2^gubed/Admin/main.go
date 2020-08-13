package main

import (
	"errors"
	"flag"
	"fmt"
	"os"
	"os/exec"
	"runtime"
	"syscall"
	"time"
)

var elfsyms *svar4
var ws syscall.WaitStatus

func main() {
	// Declaring flags for getting the binary and for toggling server/user mode
	binaryPath := flag.String("inp", "", "way")
	flag.Parse()

	if *binaryPath == "" {
		fmt.Println("No input provided")
		syscall.Exit(-1)
	}

	elfsyms = func3(*binaryPath)
	func4(elfsyms, os.Getpid())
	run(*binaryPath)
}

func run(target string) {
	runtime.LockOSThread()
	cmd := exec.Command(target)
	cmd.Stderr = nil
	cmd.Stdin = nil
	cmd.Stdout = nil
	// https://golang.org/src/syscall/exec_linux.go?s=463:2101#L12
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Ptrace: true,
	}

	cmd.Start()
	cmd.Wait()

	pid := cmd.Process.Pid
	pgid, _ := syscall.Getpgid(pid)
	assert(syscall.PtraceSetOptions(pid, syscall.PTRACE_O_TRACECLONE))
	// uncomment this line to get shell
	// shell(pid)
	err := check2(pid, "main")
	if err != nil {
		fmt.Println("Failed")
		os.Exit(-1)
	}
	check16(pid)
	for {
		val := waitForSignal(pid, pgid)
		if val == 1 {
			flagChecker(pid)
			// shell(pid)
		} else if val == 0 {
			continue
		} else {
			break
		}
	}
	fmt.Println("Done!")
	time.Sleep(2)
	runtime.UnlockOSThread()
}

func waitForSignal(pid int, pgid int) int {
	wpid, err := syscall.Wait4(-1*pgid, &ws, 0, nil)
	assert(err)
	if ws.Exited() {
		if wpid == pid {
			return -1
		}
	} else {
		// Cloning a child process also generates a trap, and we want to ignore that.
		if ws.StopSignal() == syscall.SIGTRAP {
			//fmt.Println("Stopped at a Trap")
			return 1
		} else {
			if ws.StopSignal() == syscall.SIGSEGV || ws.StopSignal() == syscall.SIGABRT {
				fmt.Println("Segmentation fault")
				os.Exit(-1)
			}
		}
	}
	return 0
}

func func1(fname string) (uint64, error) {
	for _, function := range (*elfsyms).svar6 {
		if function.Name == fname {
			return function.Offset, nil
		}
	}
	return 0, errors.New("Function not found")
}
func func2(vname string) (uint64, error) {
	for _, variable := range (*elfsyms).svar8 {
		if variable.Name == vname {
			return variable.Offset, nil
		}
	}
	return 0, errors.New("Variable not found")
}
