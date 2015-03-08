#ifndef THREADS_HEADER
#define THREADS_HEADER
#include "q.h"
#include <stdio.h>

TCB_t *runQ;

void start_thread(void (*function)(void)) {
	/* begin pseudo code
	
	allocate a stack (via malloc) of a certain size (choose 8192)
	allocate a TCB (via malloc)
	call init_TCB with appropriate arguments
	call addQ to add this TCB into the “RunQ” which is a global header pointer
	
	end pseudo code*/

	void *stackptr = (void *)malloc (8192);
	TCB_t *tcb = (TCB_t *)malloc (sizeof(TCB_t));
	init_TCB(tcb,&function,stackptr,8192);

	InitQueue(&runQ);
	TCB_t  *q1;
	InitQueue(&runQ);

	//add an element
	q1 = NewItem();
	AddQueue(&runQ,q1);
	if(runQ== NULL){
		puts("init failed...");
		return;
	}
	printQueue(runQ);
	puts("add1");

	//add this tcb
	AddQueue(&runQ, tcb);
	printQueue(runQ);
	puts("done..");

	free(q1);
	free(stackptr);
	free(tcb);

}

void run() {
	// real code
	//ucontext_t parent;     // get a place to store the main context, for faking
	//getcontext(&parent);   // magic sauce
	//swapcontext(&parent, &(RunQ->conext));  // start the first thread
}

void yield() {
	// similar to run
   //rotate the run Q;
   //swap the context, from previous thread to the thread pointed to by RunQ
}



#endif
