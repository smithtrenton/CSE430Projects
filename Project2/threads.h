#ifndef THREADS_HEADER
#define THREADS_HEADER
#include "q.h"
#include <stdio.h>

extern TCB_t *runQ; //global variable shared by other files

void start_thread(TCB_t* tcb, void (*function)(void)) {
	/* begin pseudo code
	
	allocate a stack (via malloc) of a certain size (choose 8192)
	allocate a TCB (via malloc)
	call init_TCB with appropriate arguments
	call addQ to add this TCB into the “RunQ” which is a global header pointer
	
	end pseudo code*/

	//char *stackptr = (char *)malloc (sizeof(1024));
	char stackptr[2048];
	 tcb = (TCB_t *)malloc (sizeof(TCB_t));
	init_TCB(tcb,function,stackptr,sizeof(stackptr));

    printf("tcb address: %p \n",tcb);
	printQueue(runQ);
	puts("add1");

	//add this tcb
	AddQueue(&runQ, tcb);
	printQueue(runQ);
	puts("done..");

	//free(q1);
	//free(stackptr);
	//free(tcb);

}

void run() {
	// real code
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	//(runQ->context).uc_link = &parent;
	int t = swapcontext(&parent, &(runQ->context));  // start the first thread
	if(t==-1){
		puts("swap error!");
		return;
	}

	printQueue(runQ);
	puts("\n run complete... \n");
}

void yield() {
	// similar to run
   //rotate the run Q;
   //swap the context, from previous thread to the thread pointed to by RunQ
	puts("yield");
	RotQueue(&runQ);
	printf("current head: %p\n\n", runQ);
	int t = swapcontext(&(runQ->prev->context), &(runQ->context));
	if(t==-1){
		puts("swap error!");
		return;
	}
	printf("current head: %p yield done...\n", runQ);
}



#endif
