#include "linkedList.h"
#include <stdio.h>

void* push(struct LinkedList** head, struct LinkedList** tail, void* address, size_t size) 
{
	struct LinkedList *tmp = (struct LinkedList *)malloc(sizeof(struct LinkedList));
	if (tmp == NULL)
		exit(1);

	if (*head == NULL){
		tmp->next = NULL;
		tmp->prev = NULL;
		tmp->segSize = size;
		tmp->segPtr = address;
		*head = tmp;
		*tail = *head;
		return &(tmp->segPtr);
	}

	//TODO fix push
	struct LinkedList *iteratorHead = *head;
	struct LinkedList *preiteratorHead = iteratorHead;
	while(iteratorHead->next != NULL){
		if(iteratorHead->segPtr < address)
			break;
		preiteratorHead = iteratorHead;
		iteratorHead = iteratorHead->next;
	}

	tmp->segSize = size;
	tmp->segPtr = address;
	if (iteratorHead == *head){
		tmp->next = *head;
		(*head)->prev = tmp;
		*head = tmp;
		tmp->prev = NULL;
	}
	else{
		if (iteratorHead == *tail){
			*tail = iteratorHead;
		}
		tmp->next = iteratorHead;
		iteratorHead->prev = tmp;
		preiteratorHead->next = tmp;
		tmp->prev = preiteratorHead;
	}
	return &(tmp->segPtr);
	//tmp->next = iterator;
	/*if (iterator == preiterator){
		return;
	} 
	preiterator->next = tmp;*/
}

void show(struct LinkedList* mainhead){
	struct LinkedList* head = mainhead;
	while (head != NULL){
		printf("ptr  %p\n", head->segPtr);
		printf("size %zd\n\n", head->segSize);
		head = head->next;
	}
}

size_t pop(struct LinkedList** mainhead, struct LinkedList** maintail, void* ptr) 
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
		puts("head");
		if (head == *maintail){
			*maintail = NULL;
		}
		*mainhead = (*mainhead)->next;
		prehead->next->prev = NULL;
		size = prehead->segSize;
		free(prehead);
		return size;
	}

	//tail element deletion
	if (head->next == NULL)
	{
		puts("tail");
		prehead->next = NULL;
		size = head->segSize;
		*maintail = head->prev;
		free(head);
		return size;
	}

	//in the middle
	puts("mid");
	printf("%p\n", head->segPtr);
	prehead->next = head->next;
	size = head->segSize;
	head->next->prev = head->prev;
	free(head);
	return size;
}
