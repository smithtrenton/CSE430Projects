#include "threads.h"
TCB_t *runQ;

void fun1();
void fun2();
void fun3();

void main(char** args) {

	TCB_t mainc;
	TCB_t* t1;
	TCB_t* t2;
	TCB_t* t3;

	InitQueue(&runQ);

	/*	getcontext(&t1);
	 getcontext(&ha);
	 t1.context.uc_link = &(ha);
	 t1.context.uc_stack.ss_sp = stack;
	 t1.context.uc_stack.ss_size = sizeof(stack);
	 makecontext(&t1,&testfunction,0);*/

	start_thread(t1, fun1); //note: no need to pass &testfunction
	start_thread(t2, fun2);
	start_thread(t3, fun3);
	puts("run");
	getcontext(&mainc);
	t1 = runQ;
	t2 = runQ->next;
	/*	runQ->context.uc_link = &(runQ->next->context);
	 runQ->next->context.uc_link = &mainc;*/
	run();

	puts("ok");
}

void fun1() {

	puts("This is the test function1... ");
	puts("switch to 2");

	yield();
	puts("fun1 exiting");
}

void fun2() {

	puts("This is the test function2... ");
	puts("switch to 3");

	yield();
	puts("fun2 exiting");
}

void fun3() {

	puts("This is the test function3... ");
	puts("switch to 1");
	yield();

	puts("fun3 exiting");
}
