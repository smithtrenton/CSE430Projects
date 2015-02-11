#ifndef QUEUE_HEADER
#define QUEUE_HEADER
#include <stdlib.h>

typedef struct queue {
	struct queue* prev;
	struct queue* next;
	int payload;
} queue;

queue* NewItem() {
	return (queue*)malloc(sizeof(queue));
}

void FreeItem(queue** item) {
	free(*item);
	*item = NULL;
}

void InitQueue(queue** head) {
	*head = NewItem();
	(*head)->next = NULL;
	(*head)->prev = NULL;
	(*head)->payload = -1;
}

void AddQueue(queue** head, queue* item) {
	queue* temp = *head;
	if (temp->next == NULL) {
		temp->payload = item->payload;
		temp->next = temp;
		temp->prev = temp;
		FreeItem(&item);		
	} else if (temp->next == temp) {		
		temp->next = item;
		temp->prev = item;
		item->next = temp;
		item->prev = temp;
	} else {
		while (temp->next != *head)
			temp = temp->next;
		item->next = temp->next;
		item->prev = temp;
		temp->next = item;
		(*head)->prev = item;
	}
}

queue* DelQueue(queue** head) {
	queue* delete = *head;
	if (delete->next == delete) {
		*head = NULL;
	} else {
		while (delete->next != *head) {
			delete = delete->next;
		}
		delete->prev->next = delete->next;
		delete->next->prev = delete->prev;
	}
	return delete;
}

void RotQueue(queue** head) {
	queue* temp = *head;
	*head = temp->next;
}	

void PrintQueue(queue* head) {
	if (head == NULL) {
		puts("Empty queue");
		return;
	}
	printf("queue:");
	if ((head)->next == head) {
		printf("\t%p : %d\n", head, head->payload);
	} else {
		queue* last = head;
		do {
			printf("\t%p : %d\n", last, last->payload);
			last = last->next;
		} while (last != head);
	}
}

#endif