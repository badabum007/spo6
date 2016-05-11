#include <stdio.h>
#include "linkedList.h"
#include "memManagement.h"

#define memorySize 80
char memory[memorySize];

void* my_malloc(size_t size)
{
	if(memMan.free_memory < size){
		puts("not enough memory");
		exit(1);
	}
	void* addres;
	if (addres = findFreeMem() == 0){
		puts("memory is segmented. can't find appropriate segment");
		exit(1);
	}
	else
	{
		printf("%p\n", ptr);
		printf("%zx\n", size);
		memMan.linkedList.push(addres, size); //add ptr and size to memMan
		memMan.free_memory -= size;
		return addres;
	}
}

void my_free(void* ptr)
{

}

void* findFreeMem()
{

}

/*void printmem(void* ptr)
{

}*/


struct MemoryManagement memMan;

void memoryInit()
{
	linkedList = NULL;
	memMan.maxFreeMem = memorySize;
	memMan.freeMem  = memorySize;
	memMan.memStartAddress = (void*) memory;
}

int main(int argc, char const *argv[])
{
	memoryInit();
	char* buf;
	int bufSize = 20;
	buf = (char*) my_malloc(sizeof(char)* bufSize);
	free(buf);
	return 0;
}