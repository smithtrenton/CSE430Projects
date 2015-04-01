#ifndef THREADS_HEADER
#define THREADS_HEADER
#include "q.h"
#include <stdio.h>

extern TCB_t *runQ; //global variable shared by other files

void start_thread(TCB_t* tcb, void (*function)(void)) {

	char stackptr[2048];
	tcb = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(tcb, function, stackptr, sizeof(stackptr));

	//add this tcb
	AddQueue(&runQ, tcb);
}

void run() {
	// real code
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	//(runQ->context).uc_link = &parent;
	int t = swapcontext(&parent, &(runQ->context));  // start the first thread
	if (t == -1) {
		puts("swap error!");
		return;
	}

	printQueue(runQ);
	puts("SHOULD NOT PRINT");
}

void yield() {
	// similar to run
	//rotate the run Q;
	//swap the context, from previous thread to the thread pointed to by RunQ
	RotQueue(&runQ);
	int t = setcontext(&(runQ->context));  //switch to next context
	if (t == -1) {
		puts("set error!");
		return;
	}
	puts("SHOULD NOT PRINT");
}

#endif
