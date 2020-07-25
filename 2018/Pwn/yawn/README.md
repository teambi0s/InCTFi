# yawn

**Challenge files** : [handout](Handout/)

**Author** : 4rbit3r

**Short Solution** : There is a one byte overflow one the stack which leads to a heap overflow, as the application copies data from the stack to the heap with `strcpy`. Use this to corrupt fastbin chunks and get allocation near `__malloc_hook` and overwrite that with `one_gadget`.
