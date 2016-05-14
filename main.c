#include <stdio.h>
#include "memManagement.h"
#include <string.h>

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
	push(&(memMan.listHead), &(memMan.listTail), address, size); //add ptr and size to memMan
	printf("after push head comes to %p\n", memMan.listHead);
	memMan.freeMem -= size;
	puts("free");
	printf("%zd\n", memMan.freeMem);
	puts("");
	return address;
}

void my_free(void* ptr)
{
	size_t size;
	size = pop(&(memMan.listHead), &(memMan.listTail), ptr);
	memMan.freeMem += size;
	puts("free");
	printf("%zd\n", memMan.freeMem);
	puts("");
}

void memoryInit()
{
	memMan.listHead = NULL;
	memMan.listTail = NULL;
	memMan.maxFreeMem = memorySize;
	memMan.freeMem  = memorySize;
	memMan.memStartAddress = (void*) memory;
	//printf("%p\n", memMan.memStartAddress);
}

int main(int argc, char const *argv[])
{
	//TODO fix malloc after free of smaller size
	memoryInit();
	int bufSize = 6;
	char* buf0 = (char*) my_malloc(sizeof(char)* bufSize);
	strcpy(buf0, "first");
	char* buf1 = (char*) my_malloc(sizeof(char)* bufSize);
	strcpy(buf1, "secon");
	char* buf2 = (char*) my_malloc(sizeof(char)* bufSize);
	strcpy(buf2, "third");
	char* buf3 = (char*) my_malloc(sizeof(char)* 20);
	strcpy(buf3, "fourt");

	puts(buf0);
	puts(buf1);
	puts(buf2);
	puts(buf3);

	show(memMan.listHead);
	//my_free(buf1);
	char* buf4 = (char*) my_malloc(sizeof(char)* 10);
	show(memMan.listHead);
	my_free(buf0);
	//my_free(buf3);
	printmem(&memMan);
	defrag(&memMan);

	//puts(buf0);
	puts(buf1);
	//puts(buf2);
	puts(buf3);

	/*printf("\n");
	printmem(&memMan);*/

	/*чтобы дефрагметнироватьЖ
	*возращать через указатель на указатель (void*) а сам указатель - амперсант
	*скорее всего нет
	*надо подумать
	*!!!!двухсвязный список!!!
	*/

	/* ----- протестировать работу приложки-------
	* протестировать работу после дефрагментации (адреса)
	*
	*
	*/

	return 0;
}