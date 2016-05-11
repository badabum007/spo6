#include "linkedList.h"

void push(struct LinkedList* head, void* addres, size_t size) 
{
	struct LinkedList *tmp = (struct LinkedList *)malloc(sizeof(struct LinkedList));
	if (tmp == NULL)
		exit(1);

	tmp->next = head;
	tmp->segSize = size;
	tmp->segPtr = addres;
	head = tmp;
}

void pop(struct LinkedList* head, void* ptr) 
{
	struct LinkedList* prehead = head;
	while(head != NULL){
		prehead = head;
		if (head->segPtr == ptr){
			errorFlag =
			break;
		}
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
		return
	}

	//in the middle
	prehead->next = head->next;
	free(head);
}