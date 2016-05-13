#include "linkedList.h"
#include <stdio.h>

void push(struct LinkedList** head, void* address, size_t size) 
{
	struct LinkedList *tmp = (struct LinkedList *)malloc(sizeof(struct LinkedList));
	if (tmp == NULL)
		exit(1);

	if (*head == NULL){
		tmp->next = *head;
		tmp->segSize = size;
		tmp->segPtr = address;
		*head = tmp;
		return;
	}

	//TODO fix push
	struct LinkedList *iterator = *head;
	struct LinkedList *preiterator = iterator;
	while(iterator->next != NULL){
		if(iterator->segPtr < address)
			break;
		preiterator = iterator;
		iterator = iterator->next;
	}
	tmp->next = *head;
	tmp->segSize = size;
	tmp->segPtr = address;
	*head = tmp;
	//tmp->next = iterator;
	/*if (iterator == preiterator){
		return;
	} 
	preiterator->next = tmp;*/
}

size_t pop(struct LinkedList** mainhead, void* ptr) 
{
	//puts("hello");
	size_t size;
	struct LinkedList* prehead = *mainhead;
	struct LinkedList* head = *mainhead;
	while(head != NULL){
		//puts("iter");
		if (head->segPtr == ptr)
			break;
		prehead = head;
		head = head->next;
	}
	if (head == NULL){
		puts("double my_free() or corruption");
		exit(1);
	}

	//from head
	if (prehead == head){
		//puts("head");
		head = head->next;
		size = prehead->segSize;
		free(prehead);
		return size;
	}

	//tail element deletion
	if (head->next == NULL)
	{
		//puts("tail");
		prehead->next = NULL;
		size = head->segSize;
		free(head);
		return size;
	}

	//in the middle
	//puts("middle");
	puts("mid");
	printf("%p\n", head->segPtr);
	prehead->next = head->next;
	size = head->segSize;
	free(head);
	return size;
}