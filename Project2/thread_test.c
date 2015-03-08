#include "threads.h"

void main(char** args) {

	testfunction();

	/*	TCB_t  *head,*q1, *q2;
	 InitQueue(&head);

	 q1 = NewItem();
	 AddQueue(&head,q1);
	 if(head== NULL){
	 puts("init failed...");
	 return;
	 }
	 printQueue(head);
	 puts("add1");

	 q2 = NewItem();
	 AddQueue(&head,q2);
	 printQueue(head);*/
	//pointer to function
	/*	void (*fun_ptr)(void);
	 fun_ptr = &testfunction;*/
	start_thread(&testfunction);

	puts("add2");

	//free(q1);

}

void testfunction() {

	puts("This is the test function... \n");
}


