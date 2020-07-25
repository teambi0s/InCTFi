# securepad  

**Challenge files** : [handout](Handout/)

**Author** : 4rbit3r

**Short Solution** : Un-initialised stack pointer leading to UAF(); free fake small bin chunk to get libc leak, perform a simple fastbin corrution to overwrite malloc_hook with onegadget and get shell.

