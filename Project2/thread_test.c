#include "threads.h"

#define NUM_THREADS 15
TCB_t *runQ;
int count = 0;

void test();

void main(char** args) {

	TCB_t* threads[NUM_THREADS];

	InitQueue(&runQ);

	/*	start_thread(t1, fun1); //note: no need to pass &testfunction
	 start_thread(t2, fun2);
	 start_thread(t3, fun3);*/
	int i = 0;
	for (i = 0; i < NUM_THREADS; i++) {
		start_thread(threads[i], test); //note: no need to pass &testfunction
	}

	puts("run");

	run();

	puts("ok");
}

void test() {
	while (count < 100) {
		printf("This is the test function %d... \n", count);
		puts("switching");
		count++;
		yield();
		//swapcontext(&(t3->context),&(t1->context));
		puts("function exiting");
	}
	puts("function end");
}
