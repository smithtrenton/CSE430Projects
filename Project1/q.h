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
	*head = NULL;
}

void AddQueue(queue** head, queue* item) {
	queue* temp = *head;
	if (temp == NULL) {
		*head = item;	
		(*head)->next = *head;
		(*head)->prev = *head;
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
	queue* del = *head;
	if (del->next == del) {
		*head = NULL;
	} else {
		while (del->next != *head) {
			del = del->next;
		}
		del->prev->next = del->next;
		del->next->prev = del->prev;
	}
	return del;
}

void RotQueue(queue** head) {
	if (head != NULL) {
		queue* temp = *head;
		*head = temp->next;
	}
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