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

void pop(struct LinkedList* head, void* ptr) 
{
	struct LinkedList* prehead = head;
	while(head != NULL){
		prehead = head;
		if (head->segPtr == ptr)
			break;
		head = head->next;
	}
	if (head == NULL){
		puts("double my_free() or corruption");
		exit(1);
	}

	//from head
	if (prehead == head){
		head = head->next;
		free(prehead);
		return;
	}

	//tail element deletion
	if (head->next == NULL)
	{
		prehead->next = NULL;
		free(head);
		return;
	}

	//in the middle
	prehead->next = head->next;
	free(head);
}