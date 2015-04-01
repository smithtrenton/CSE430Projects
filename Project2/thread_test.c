/* 
 * 
 * CSE 430 
 * Project 2
 * Authors: Trenton Smith, Junyu Chen
 *  
 */
#include "threads.h"

#define NUM_THREADS 3
int count = 0;
TCB_t *runQ = 0;

void test1();
void test2();

void main(char** args) {

	TCB_t* threads[NUM_THREADS];

	printf("Initializing %d threads\n", NUM_THREADS);
	InitQueue(&runQ);
	int i = 0;
	for (i = 0; i < NUM_THREADS; i++) {
		start_thread(threads[i], (i%2 == 0) ? test1 : test2); 
	}
	
	puts("runQ content: ");
	printQueue(runQ);

	puts("\nStarting threads\n");

	run();

	puts("Run ended");
}

void test1() {
	int i = 0;
	while (count >= 0) {
		printf("test1 = Swapped %d : CurrentThread %p : Visited %d \n", 
			count, runQ, ++i);
		count++;
		sleep(1);
		puts("test1 - swapping"); 
		yield();
		puts("test1 - post yield");
	}
	puts("test1 - loop end");
}

void test2() {
	int x = 0;
	while (count >= 0) {
		printf("test2 = Swapped %d : CurrentThread %p : Visited %d \n", 
			count, runQ, ++x);
		count++;
		sleep(1);
		puts("test2 - swapping");
		yield();
		puts("test2 - post yield");
	}
	puts("test2 - loop end");
}
