#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int bi0s = 1337;
char shellcode[] = "\x55\x48\x89\xE5\x48\x31\xC0\x48\x31\xDB\x48\x31\xC9\x48\x31\xD2\xB8\x09\x70\x33\x13\xB9\xC9\xC3\x90\x90\x67\x89\x48\x04\xEB\xE4\xC9\xC3"; 
char shellcode2[] = "\x55\x48\x89\xE5\xB0\x08\xB3\x04\xB1\x02\xC9\xC3";

/*
 * We will break at deep and then add break points for the memory region that's now inserted.
 * After deep we will add breakpoints at the addresses - 0x13337000 and 0x1333700d
 * Then we hit 0x13337000 and make sure that we reached there.
 * Then 0x1333700d needs to be hit
 * Then we need to rehit 0x1333700d and not 0x13337000
 * Then we need to make sure that we changed the values that was hit
 * Then we need to hit the mem unmap function 
 */
void deep(void *ptr) {
	(*(void (*)()) ptr)();
}

void *giveme(unsigned long long addr) {
	void* ptr;
	ptr = mmap((void *)addr, 4096, PROT_READ |PROT_WRITE |PROT_EXEC, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if (ptr == MAP_FAILED) {
		exit(-1);
	}
	return ptr;
}

void takeaway(void *ptr) {
	if (munmap(ptr, 4096) != 0) {
		exit(-1);
	}
}

int check() {
	void *ptr = giveme(0x13337000);
	memcpy(ptr, shellcode, strlen(shellcode));
	deep(ptr);
	takeaway(ptr);
	bi0s = 0x1337;
	ptr = giveme(0x51dd0000);
	memcpy(ptr, shellcode2, strlen(shellcode));
	deep(ptr);
	takeaway(ptr);
}

int end() {
	int a;
	return 0;
}

int main() {
	check();
	end();
}
