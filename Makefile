CC 			= gcc
CFLAGS 		= -c -Wall -pedantic

all: output

output: main.o memManagement.o linkedList.o
	$(CC) memManagement.o linkedList.o  main.o -o lab
	
main.o: main.c
	$(CC) $(CFLAGS) main.c

memManagement.o: memManagement.c
	$(CC) $(CFLAGS) memManagement.c 

linkedList.o: linkedList.c
	$(CC) $(CFLAGS) linkedList.c

clean:
	rm -r *.o lab
