#ifndef THREADS_HEADER
#define THREADS_HEADER
#include "q.h"

extern TCB_t *runQ; //global variable shared by other files

void start_thread(TCB_t* tcb, void (*function)(void)) {

	void *stackptr = malloc(8192);
	tcb = (TCB_t *) malloc(sizeof(TCB_t));
	init_TCB(tcb, function, stackptr, 8192);

	//add this tcb
	AddQueue(&runQ, tcb);
}

void run() {
	// real code
	ucontext_t parent;     // get a place to store the main context, for faking
	getcontext(&parent);   // magic sauce
	swapcontext(&parent, &(runQ->context));  // start the first thread
}

void yield() {
	// similar to run
	//rotate the run Q;
	//swap the context, from previous thread to the thread pointed to by RunQ
	TCB_t *temp = runQ;
	RotQueue(&runQ);
	swapcontext(&(temp->context), &(runQ->context)); //switch to next context
}

#endif
