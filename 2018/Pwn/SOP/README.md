# SOP  

**Challenge files** : [handout](Handout/)

**Author** : mahesh, sherl0ck

**Short Solution** : Arbitary read and write; use DynELF to overwrite "exit" with "system" in STR_TAB, then overwrite stdin vtable with exit@plt to get shell or else find the address of "system", overwrite stdin with "/bin/sh", overwrite setvbuf with system and then overwrite exit's got with init(). 

