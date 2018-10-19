# lost  

**Challenge files** : [handout](Handout/)

**Author** : sherl0ck

**Short Solution** : Race condition in `alloc` leads to a huge heap overflow. Use this to overwrite top chunk size to fastbin size and then use fastbin dup to allocate chunk in bss and overwrite `ptr`.

**Detailed Write-up** : [vigneshsrao.github.io/lost](https://vigneshsrao.github.io/lost/)
