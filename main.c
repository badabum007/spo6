#include <stdio.h>
#include "memManagement.h"
#include <string.h>

#define memorySize 80
char memory[memorySize];
struct MemoryManagement memMan;

void** my_malloc(size_t size)
{
	if (size == 0)
		return NULL;
	if(memMan.freeMem < size){
		puts("not enough memory");
		exit(1);
	}
	void* address;
	address = findFreeMem(&memMan, size);
	void** ptrToAddress;
	ptrToAddress = push(&(memMan.listHead), &(memMan.listTail), address, size); //add ptr and size to memMan
	memMan.freeMem -= size;
	return ptrToAddress;
}

void my_free(void* ptr)
{
	size_t size;
	size = pop(&(memMan.listHead), &(memMan.listTail), ptr);
	memMan.freeMem += size;
}

void memoryInit()
{
	memMan.listHead = NULL;
	memMan.listTail = NULL;
	memMan.maxFreeMem = memorySize;
	memMan.freeMem  = memorySize;
	memMan.memStartAddress = (void*) memory;
}

int main(int argc, char const *argv[])
{
	memoryInit();
	int bufSize = 20;
	char **buf0, **buf1, **buf2, **buf3, **buf4;
	buf0 = (char**) my_malloc(sizeof(char)* bufSize);
	strcpy(*buf0, "null");
	buf1 = (char**) my_malloc(sizeof(char)* 20);
	strcpy(*buf1, "first");
	buf2 = (char**) my_malloc(sizeof(char)* bufSize);
	strcpy(*buf2, "second");
	buf3 = (char**) my_malloc(sizeof(char)* 20);
	strcpy(*buf3, "third");

	puts(*buf0);
	puts(*buf1);
	puts(*buf2);
	puts(*buf3);

	my_free(*buf1);
	my_free(*buf3);
	printmem(&memMan);
	buf4 = (char**) my_malloc(sizeof(char)* 30);
	strcpy(*buf4, "fourth");
	printmem(&memMan);

	puts(*buf0);
	puts(*buf2);
	puts(*buf4);

	return 0;
}
