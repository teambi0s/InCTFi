# echo

**Challenge files** : [handout](Handout/)

**Author** : night_f0x

**Short Solution** : There is a overflow in the `bss` which allows to overwrite a function pointer , Since there is no `NX` inside qemu we can write shellcode. We have to write alphanumeric shellcode, since only alphanumeric charecters are allowed as input.
