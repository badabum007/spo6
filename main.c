#include <stdio.h>
#include "memManagement.h"

#define memorySize 80
char memory[memorySize];
struct MemoryManagement memMan;

void* my_malloc(size_t size)
{
	if(memMan.freeMem < size){
		puts("not enough memory");
		exit(1);
	}
	void* address;
	address = findFreeMem(&memMan, size);
	printf("%p\n", address);
	printf("%zx\n", size);
	//push(memMan.linkedList, address, size); //add ptr and size to memMan
	memMan.freeMem -= size;
	return address;
}

/*void my_free(void* ptr)
{

}*/

/*void printmem(void* ptr)
{

}*/

void memoryInit()
{
	memMan.linkedList = NULL;
	memMan.maxFreeMem = memorySize;
	memMan.freeMem  = memorySize;
	memMan.memStartAddress = (void*) memory;
}

int main(int argc, char const *argv[])
{
	puts("OK");
	/*memoryInit();
	char* buf;
	int bufSize = 20;
	buf = (char*) my_malloc(sizeof(char)* bufSize);*/
	//free(buf);
	return 0;
}