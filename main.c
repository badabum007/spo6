#include <stdio.h>
#include "memManagement.h"

#define memorySize 80
char memory[memorySize];
struct MemoryManagement memMan;

void* my_malloc(size_t size)
{
	if (size == 0)
		return NULL;
	if(memMan.freeMem < size){
		puts("not enough memory");
		exit(1);
	}
	void* address;
	address = findFreeMem(&memMan, size);
	printf("%p\n", address);
	printf("%zd\n", size);
	push(&(memMan.linkedList), address, size); //add ptr and size to memMan
	printf("after push head comes to %p\n", memMan.linkedList);
	memMan.freeMem -= size;
	puts("free");
	printf("%zd\n", memMan.freeMem);
	puts("");
	return address;
}

void my_free(void* ptr)
{
	size_t size;
	size = pop(&(memMan.linkedList), ptr);
	memMan.freeMem += size;
	puts("free");
	printf("%zd\n", memMan.freeMem);
	puts("");
}

/*void printmem(void* ptr)
{

}*/

void memoryInit()
{
	memMan.linkedList = NULL;
	memMan.maxFreeMem = memorySize;
	memMan.freeMem  = memorySize;
	memMan.memStartAddress = (void*) memory;
	//printf("%p\n", memMan.memStartAddress);
}

int main(int argc, char const *argv[])
{
	//TODO fix malloc after free of smaller size
	memoryInit();
	int bufSize = 20;
	char* buf0 = (char*) my_malloc(sizeof(char)* bufSize);
	char* buf1 = (char*) my_malloc(sizeof(char)* 16);
	char* buf2 = (char*) my_malloc(sizeof(char)* bufSize);
	char* buf3 = (char*) my_malloc(sizeof(char)* 16);
	my_free(buf1);
	char* buf4 = (char*) my_malloc(sizeof(char)* bufSize);

	return 0;
}