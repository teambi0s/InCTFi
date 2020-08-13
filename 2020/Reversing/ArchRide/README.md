# ArchRide


### Challenge Description

I have a long one planned. Buckle up!
Limit your character check to the printable range please :)

### Challenge Authors
@4lex1 @Mr_UnKnOwN

### Flag
```
inctf{x32_x64_ARM_MAC_powerPC_4rch_maz3_6745}
```
### Issues Faced

The issues faced :- One particular level(4) of this challenge allowed multiple inputs to parse, which gave a corrupted bzip file output.

### Solution 

The challenge solution script has been added under Admin/Solution which is the intended solution. The unintended approach is that the header of the bzip can be used to bruteforce the inout to each level and the binaries can be emulated and run in the various archs to get the flag.
  - Total no of levels: 120
