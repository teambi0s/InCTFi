#include <iostream>
#include <Windows.h>

HANDLE hStdin;
HANDLE hStdout;

typedef struct {
	DWORD size;
	char* data;

} st;

#define lim 10
st* list[lim];
HANDLE hHeap;
BOOL flag = 2;

int initialize() {
	hHeap = HeapCreate(0, 0, 0);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	return 0;
}

int add() {
	DWORD size = 0;
	printf("Enter size: ");
	scanf_s("%d", &size);
	if (size < 0 || size>0x3000) {
		printf("Invalid size\n");
		return -1;
	}

	st* temp = NULL;
	DWORD i = 0;
	for (i = 0; i < lim; i++) {
		if (list[i] == NULL) {
			temp = (st*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(st));
			temp->size = size;
			temp->data = (char*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, size);
			list[i] = temp;
			printf("Allocated\n\n");
			break;
		}
	}
	if (i == lim) {
		printf("No More Allocations\n\n");
		return -1;
	}
	return 0;
}

int remove() {
	DWORD idx = 0;
	printf("Enter idx: ");
	scanf_s("%d", &idx);
	if (idx >= lim || idx < 0) {
		printf("Invalid index\n\n");
		return -1;
	}
	if (list[idx] == (st*)-1 || list[idx] == NULL) {
		printf("Not a valid pointer\n\n");
		return -1;
	}
	HeapFree(hHeap, 0, list[idx]->data);
	HeapFree(hHeap, 0, list[idx]);
	list[idx] = (st*)-1;
	printf("Removed\n\n");

	return 0;
}

int view() {
	if (flag == 0) {
		printf("No More Viewing\n\n");
		return -1;
	}
	flag--;
	DWORD idx = 0;
	printf("Enter idx: ");
	scanf_s("%d", &idx);
	if (idx >= lim || idx < 0) {
		printf("Invalid index\n\n");
		return -1;
	}
	if (list[idx] == (st*)-1 || list[idx] == NULL) {
		printf("Not a valid pointer\n\n");
		return -1;
	}

	printf("Data: %s\n", list[idx]->data);
	return 0;
}


int edit() {
	DWORD idx = 0;
	printf("Enter idx: ");
	scanf_s("%d", &idx);
	if (idx >= lim || idx < 0) {
		printf("Invalid index\n\n");
		return -1;
	}
	if (list[idx] == (st*)-1 || list[idx] == NULL) {
		printf("Not a valid pointer\n\n");
		return -1;
	}
	st* temp = list[idx];

	INT offset = 0;
	printf("Enter offset: ");
	scanf_s("%d", &offset);

	INT size = 0;
	printf("Enter size: ");
	scanf_s("%d", &size);
	if (size < 0 || size > temp->size) {
		printf("Invalid size\n\n");
		return -1;
	}

	if ((offset + size) > (INT)temp->size) {
		printf("Invalid offset\n\n");
		return -1;
	}

	printf("Enter data: ");
	if (!ReadFile(hStdin, temp->data + offset, size, NULL, NULL)) {
		printf("Error");
		ExitProcess(EXIT_FAILURE);
	}

}

DWORD menu() {
	printf("-----NtBabyHeap-----\n");
	printf("1. Add\n");
	printf("2. Remove\n");
	printf("3. View\n");
	printf("4. Edit\n");
	printf("Enter Choice: ");
	DWORD choice;
	scanf_s("%d", &choice);

	return choice;
}


int main() {
	initialize();
	while (TRUE) {
		switch (menu()) {
		case 1: add();
			break;
		case 2: remove();
			break;
		case 3: view();
			break;
		case 4: edit();
			break;
		default: ExitProcess(0);
		}

	}
}

