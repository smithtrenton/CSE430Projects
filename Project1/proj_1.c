#include "q.h"

int main() {
	puts("begin\n");
	queue *head=NULL;
	printf("null head %p\n",head);
	
	InitQueue(&head);
	printf("initialized head %p\n",head);

	//create and add new elements
	puts("\ncreating elements");
	queue *q = NewItem();
	queue *q2 = NewItem();
	queue *q3 = NewItem();
	q->payload = 1;
	q2->payload = 2;
	q3->payload = 3;
	printf("q: %p : %d\n", q, q->payload);
	printf("q2: %p : %d\n", q2, q2->payload);
	printf("q3: %p : %d\n", q3, q3->payload);

	puts("\nadding elements");
	AddQueue(&head, q);
	PrintQueue(head);
	puts("\n");
	AddQueue(&head, q2);
	PrintQueue(head);
	puts("\n");
	AddQueue(&head, q3);
	PrintQueue(head);
	
	puts("\nrotating elements");
	RotQueue(&head);
	PrintQueue(head);
	puts("");
	RotQueue(&head);
	PrintQueue(head);
	puts("");
	RotQueue(&head);
	PrintQueue(head);

	//free all elements
	puts("\ndeleting elements");
	queue* temp = DelQueue(&head);
	printf("delete: %p\t %d\n", temp, temp->payload);
	FreeItem(&temp);
	printf("deleted: %p\n", temp);
	PrintQueue(head);
	puts("\n");
	temp = DelQueue(&head);
	printf("delete: %p\t %d\n", temp, temp->payload);
	FreeItem(&temp);
	PrintQueue(head);
	puts("\n");
	temp = DelQueue(&head);
	printf("delete: %p\t %d\n", temp, temp->payload);
	FreeItem(&temp);
	PrintQueue(head);
	
	puts("end");
	return 0;
}