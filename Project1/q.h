#ifndef queue
#define queue
#include <stdlib.h>

typedef struct queue queue;

struct queue {
	queue *prev;
	queue *next;
	int payload;
};

queue *NewItem() {
	return malloc(sizeof(queue));
}

void FreeItem(queue *item) {
	free(item);
}

void InitQueue(queue *head) {
	head = NewItem();
	head->next = head;
	head->prev = head;
}

void AddQueue(queue *head, queue *item) {
	queue *last = head;
	while (last->next != head) {
		last = last->next;
	}
	item->prev = last;
	item->next = head;
	last->next = item;	
	head->prev = item;
}

queue *DelQueue(queue *head) {
	queue *delete = head;
	while (delete->next != head) {
		delete = delete->next;
	}
	delete->prev->next = delete->next;
	delete->next->prev = delete->prev;
	return delete;
}

void RotateQ(queue *head) {
	queue *temp = head;
	head = temp->next;
}	

#endif