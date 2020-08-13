package main

import (
	"fmt"
	"math"
	"os"
)

var state int = 0
var vala uint64 = 0
var valb uint64 = 0
var valc uint64 = 0

/*
	Breakpoints -
		main - 1
		deep - 2
		giveme - 3
		check - 5
		takeaway - 4
		0x13337000 - 6
		0x1333700d - 7

		0x51dd0000 - 8

		0x51dd0004
		0x51dd0006
		0x51dd0008

	Variables -
		bi0s
		flag

*/

func flagChecker(pid int) {
	//check18(pid)
	switch state {
	case 0:
		//fmt.Println("First - correct")
		err := check2(pid, "deep")
		if err != nil {
			state = 2344
		} else {
			state = 2557
		}
		// if true go to state else go to some random value
		flagChecker(pid)
	case 7:
		//fmt.Println("46th - c")
		val, _ := check23(pid, "Rbx")
		valb = val
		state = 69
		check17(pid)
	case 12:
		//fmt.Println("27th - c")
		currentbp, err := check10(0x1333700d)
		// enable the current breakpoint
		err = check13(pid, currentbp)
		assert(err)
		state = 5012
		check16(pid)
	case 69:
		//fmt.Println("47th - c")
		val, _ := check23(pid, "Rcx")
		valc = val
		state = 70
		check17(pid)
	case 70:
		//fmt.Println("48th - c")
		if math.Pow(float64(vala), 2)+math.Pow(float64(valb), 3) == math.Pow(float64(valc), 7) {
			state = 1020
		} else {
			state = 123123
		}
		flagChecker(pid)
	case 99:
		if check14() == 0xffff {
			//fmt.Println("amazing")
			printFlag()
		}
		state = 33
		check16(pid)
	case 435:
		//fmt.Println("36th - c")
		state = 8008
		check16(pid)
	case 765:
		//fmt.Println("14th - c")
		err := check3(pid, "0x13337000")
		if err != nil {
			state = 1230
		} else {
			state = 3231
		}
		flagChecker(pid)
	case 987:
		//fmt.Println("7th - correct")
		state = 7562
		check16(pid)
	case 1020:
		//fmt.Println("49th - c")
		state = 1021
		check16(pid)
	case 1021:
		//fmt.Println("50th - c")
		// Done with the adventures - now we are at takeaway
		if check8(pid) == 4 {
			state = 3917
		} else {
			state = 9293
		}
		flagChecker(pid)
	case 1024:
		//fmt.Println("41st - c")
		if check8(pid) == 8 {
			currentbp, err := check10(0x51dd0000)
			// disable the current breakpoint
			err = check15(pid, currentbp)
			assert(err)
			rip, _ := check23(pid, "Rip")
			check24(pid, "Rip", rip-1)
			check11(pid, 8)
			state = 2579
		} else {
			state = 9989
		}
		flagChecker(pid)
	case 1111:
		//fmt.Println("22nd - c")
		// should again reach 0x1333700d
		state = 7777
		check17(pid)
	case 1142:
		//fmt.Println("Fourth - c")
		err := check2(pid, "takeaway")
		if err != nil {
			state = 1233
		} else {
			state = 9999
		}
		flagChecker(pid)
	case 1999:
		//fmt.Println("9th - c")
		data, err := check5(pid, "bi0s")
		if err != nil {
			state = 9238
		} else {
			if data == 1337 {
				state = 6465
			} else {
				state = 123
			}
		}
		flagChecker(pid)
	case 2020:
		//fmt.Println("38th - c")
		err := check3(pid, "0x51dd0000")
		if err != nil {
			state = 3570
		} else {
			state = 8642
		}
		flagChecker(pid)
	case 2314:
		//fmt.Println("Third - c")
		err := check2(pid, "giveme")
		if err != nil {
			state = 434
		} else {
			state = 1142
		}
		flagChecker(pid)
	case 2333:
		//fmt.Println("31st - c")
		err := check3(pid, "0x51dd0000")
		if err != nil {
			state = 3579
		} else {
			state = 1290
		}
		flagChecker(pid)
	case 2557:
		//fmt.Println("Second - incorrect")
		err := check3(pid, "0x13337000")
		if err != nil {
			state = 2314
		} else {
			state = 1246
		}
		flagChecker(pid)
	case 2579:
		//fmt.Println("43rd - c")
		// 0x51dd0001
		state = 2581
		check17(pid)
	case 2581:
		//fmt.Println("44rd - c")
		// 0x51dd0004
		state = 2582
		check17(pid)
	case 2582:
		//fmt.Println("45rd - c")
		// 0x51dd0006
		val, _ := check23(pid, "Rax")
		vala = val
		state = 7
		check17(pid)
	case 2900:
		//fmt.Println("17th - c")
		if check8(pid) == 6 {
			state = 8997
		} else {
			state = 1279
		}
		flagChecker(pid)
	case 3231:
		//fmt.Println("15th - ic")
		err := check3(pid, "0x51dd0000")
		if err != nil {
			state = 4000
		} else {
			state = 1290
		}
		flagChecker(pid)
	case 3339:
		//fmt.Println("30th - c")
		if check8(pid) == 4 {
			state = 2333
		} else {
			state = 9290
		}
		flagChecker(pid)
	case 3400:
		//fmt.Println("25th - c")
		// 0x1333700d + 3
		state = 9800
		check17(pid)
	case 3579:
		//fmt.Println("32nd - c")
		state = 3600
		check16(pid)
	case 3600:
		//fmt.Println("33rd - c")
		if check8(pid) == 3 {
			data, err := check5(pid, "bi0s")
			if err != nil {
				state = 1220
			} else {
				if data == 0x1337 {
					state = 5432
				} else {
					state = 1220
				}
			}
		} else {
			state = 1220
		}
		flagChecker(pid)
	case 3917:
		//fmt.Println("51 - c")
		err := check2(pid, "end")
		if err != nil {
			state = 71712
		} else {
			state = 7172
		}
		flagChecker(pid)
	case 3999:
		//fmt.Println("12th - c")
		state = 8080
		check16(pid)
	case 4000:
		//fmt.Println("16th - c")
		// continue to 0x13337000
		state = 2900
		check16(pid)
	case 4401:
		//fmt.Println("21 - c")
		// now we are at 0x1333700d
		if check8(pid) == 7 {
			state = 1111
		} else {
			state = 2200
		}
		flagChecker(pid)
	case 4987:
		//fmt.Println("35th - c")
		err := check3(pid, "0x51dd0000")
		if err != nil {
			state = 435
		} else {
			state = 2202
		}
		flagChecker(pid)
	case 5012:
		//fmt.Println("28th - c")
		if check8(pid) == 7 {
			state = 8001
		} else {
			state = 2122
		}
		flagChecker(pid)
	case 5342:
		//fmt.Println("Sixth - correct")
		err := check2(pid, "check")
		if err != nil {
			state = 8050
		} else {
			state = 987
		}
		flagChecker(pid)
	case 5432:
		//fmt.Println("34th - c")
		// at this point we need to make
		err := check3(pid, "0x1333700e")
		if err != nil {
			state = 4987
		} else {
			state = 1321
		}
		flagChecker(pid)
	case 6420:
		//fmt.Println("40th - c")
		state = 1024
		check16(pid)
	case 6465:
		//fmt.Println("10th - c")
		state = 9000
		check16(pid)
	case 6666:
		//fmt.Println("24th - c")
		// 0x1333700d + 2
		currentbp, err := check10(0x1333700d)
		// disable the current breakpoint
		err = check15(pid, currentbp)
		assert(err)
		state = 3400
		check17(pid)
	case 7172:
		//fmt.Println("52nd - c")
		state = 9531
		check16(pid)
	case 7562:
		//fmt.Println("8th - correct")
		// we check if the current break point is check
		if check8(pid) == 5 {
			state = 1999
		} else {
			state = 7543
		}
		flagChecker(pid)
	case 7777:
		//fmt.Println("23rd - c")
		// 0x1333700d + 1
		state = 6666
		check17(pid)
	case 8001:
		//fmt.Println("29th - c")
		// now we are supposed to exit the function need to continue
		state = 3339
		check16(pid)
	case 8008:
		//fmt.Println("37th - c")
		// should be at deep
		if check8(pid) == 2 {
			state = 2020
		} else {
			state = 9877
		}
		flagChecker(pid)
	case 8080:
		//fmt.Println("13th - c")
		// now we are at deep
		if check8(pid) == 2 {
			state = 765
		} else {
			state = 7683
		}
		flagChecker(pid)
	case 8642:
		//fmt.Println("39th - c")
		err := check3(pid, "0x1333700e")
		if err != nil {
			state = 6420
		} else {
			state = 129
		}
		flagChecker(pid)
	case 8997:
		//fmt.Println("18th - c")
		err := check3(pid, "0x1333700d")
		if err != nil {
			state = 4657
		} else {
			state = 9400
		}
		flagChecker(pid)
	case 9000:
		//fmt.Println("11th - correct")
		// now at giveme
		if check8(pid) == 3 {
			state = 3999
		} else {
			state = 8776
		}
		flagChecker(pid)
	case 9400:
		//fmt.Println("20th - c")
		state = 4401
		// continue to 0x1333700d
		check16(pid)
	case 9531:
		//fmt.Println("54th - c")
		err := check3(pid, "0x51dd0006")
		if err != nil {
			state = 99
		} else {
			state = 12931
		}
		flagChecker(pid)
	case 9800:
		//fmt.Println("26th - c")
		// 0x1333700d + step
		state = 12
		check17(pid)
	case 9999:
		//fmt.Println("Fifth - incorrect")
		err := check3(pid, "0x51dd0000")
		if err != nil {
			state = 5342
		} else {
			state = 899
		}
		flagChecker(pid)
	default:
		//fmt.Printf("Failed! Badly : %d\n", state)
		os.Exit(-1)
	}
}

func printFlag() {
	fmt.Println("inctf{fake_flag}")
	os.Exit(0)
}

// func shell(pid int) {
// 	getInfo(pid)
// 	fmt.Println(pid)
// 	reader := bufio.NewReader(os.Stdin)
// 	fmt.Print("\n>> ")
// 	command, _ := reader.ReadString('\n')
// 	command = strings.TrimSpace(command)
// 	pieces := strings.Split(command, " ")
// 	if strings.HasPrefix(command, "break") {
// 		if len(pieces) == 2 {
// 			if strings.HasPrefix(pieces[1], "0x") {
// 				err := check3(pid, pieces[1])
// 				if err != nil {
// 					ShowError(pid, command)
// 				}
// 			} else {
// 				err := check2(pid, pieces[1])
// 				if err != nil {
// 					ShowError(pid, command)
// 				}
// 			}
// 		} else {
// 			ShowError(pid, command)
// 		}
// 		shell(pid)
// 	} else if strings.HasPrefix(command, "continue") {
// 		check16(pid)
// 	} else if strings.HasPrefix(command, "step") {
// 		check17(pid)
// 	} else if strings.HasPrefix(command, "delete") {
// 		if len(pieces) == 3 {
// 			if pieces[1] == "breakpoint" {
// 				i, err := strconv.Atoi(pieces[2])
// 				if err != nil {
// 					ShowError(pid, command)
// 				}
// 				check11(pid, i)
// 			} else {
// 				ShowError(pid, command)
// 			}
// 		} else {
// 			ShowError(pid, command)
// 		}
// 		shell(pid)
// 	} else if strings.HasPrefix(command, "show") {
// 		if len(pieces) == 2 {
// 			if pieces[1] == "breakpoint" {
// 				check12(pid)
// 			} else if pieces[1] == "register" {
// 				showRegisters(pid)
// 			} else {
// 				ShowError(pid, command)
// 			}
// 		} else {
// 			ShowError(pid, command)
// 		}
// 		shell(pid)
// 	} else if strings.HasPrefix(command, "print") {
// 		if len(pieces) == 3 {
// 			if pieces[1] == "register" {
// 				check25(pid, pieces[2])
// 			} else {
// 				ShowError(pid, command)
// 			}
// 		} else {
// 			ShowError(pid, command)
// 		}
// 		shell(pid)
// 	} else if strings.HasPrefix(command, "read") {
// 		if len(pieces) == 3 {
// 			if pieces[1] == "memory" {
// 				if strings.HasPrefix(pieces[2], "0x") {
// 					data, err := check6(pid, pieces[2])
// 					if err != nil {
// 						showIssue(err)
// 					}
// 					fmt.Println(data)
// 				} else {
// 					data, err := check5(pid, pieces[2])
// 					if err != nil {
// 						showIssue(err)
// 					}
// 					fmt.Println(data)
// 				}
// 			} else {
// 				ShowError(pid, command)
// 			}
// 		} else {
// 			ShowError(pid, command)
// 		}
// 		shell(pid)
// 	} else {
// 		ShowError(pid, command)
// 		shell(pid)
// 	}
// }

// func ShowError(pid int, command string) {
// 	fmt.Println(command + " isn't recognized")
// }

// func showIssue(err error) {
// 	fmt.Println(err)
// }
