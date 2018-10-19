# feedback

**Challenge files** : [handout](Handout/)

**Author** : sherl0ck

**Short Solution** : Use the one-byte overflow in `update_name` for House of Einherjar and get overlapping chunks. Then use unsortedbin attack to overwrite stdin's `_IO_buf_end` with main_arena address and use `scanf` call to overwrite `__malloc_hook` with [one_gadget](https://github.com/david942j/one_gadget).

**Detailed Write-up** : [vigneshsrao.github.io/feedback](https://vigneshsrao.github.io/feedback/)
