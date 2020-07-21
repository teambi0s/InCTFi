Assembly instructions doc

Instruction set "str", "ld", "in", "out", "mov", "chk", "xor", "mul", "shl", "shr", "add", "hlt", "jmp", "chkflag", "imod"

## store and load instructions

str reg <reg> <reg>
str addr <reg> <address>

## in and out instruction

in <reg>

## xor and mul instrucion

xor <reg> <reg> <reg>

## shift left and shift right

shl <reg> <constant>

## chkflag and hlt

chkflag

## add instrucion

add <reg> <reg> <constant>

## jmp instruction

jmp set <address>

jmp chk <address>

jmp ip <address>

## mov instruction 

mov reg <reg> <reg>
mov cnt <reg> <constant>

## imod instruction

imod set <address> <reg> <reg>
imod mod <address> <reg> <reg>

## chk instruction

chk eq <reg> <reg>
chk gt <reg> <reg>
chk lt <reg> <reg>
