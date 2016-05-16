#include <stdio.h>
#include "memManagement.h"
#include <string.h>

#define memorySize 80
char memory[memorySize];
struct MemoryManagement memMan;

int main(int argc, char const *argv[])
{
	memoryInit(&memMan, memorySize, (void*)(&memory));
	int bufSize = 20;
	char **buf0, **buf1, **buf2, **buf3, **buf4;
	buf0 = (char**) my_malloc(&memMan, sizeof(char)* bufSize);
	strcpy(*buf0, "null");
	buf1 = (char**) my_malloc(&memMan, sizeof(char)* bufSize);
	strcpy(*buf1, "first");
	buf2 = (char**) my_malloc(&memMan, sizeof(char)* bufSize);
	strcpy(*buf2, "second");
	buf3 = (char**) my_malloc(&memMan, sizeof(char)* bufSize);
	strcpy(*buf3, "third");

	puts(*buf0);
	puts(*buf1);
	puts(*buf2);
	puts(*buf3);

	my_free(&memMan, *buf1);
	my_free(&memMan, *buf3);
	printmem(&memMan);
	buf4 = (char**) my_malloc(&memMan, sizeof(char)* 30);
	strcpy(*buf4, "fourth");
	int **array;
	array = (int**) my_malloc(&memMan, sizeof(int)* 2);
	*(*array)= 4;
	*(*array + 1) = 9;
	printf("%d\n", **array);
	printf("%d\n", *(*array + 1));
	printmem(&memMan);

	puts(*buf0);
	puts(*buf2);
	puts(*buf4);

	return 0;
}
