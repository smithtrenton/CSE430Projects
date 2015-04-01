/* 
 * 
 * CSE 430 
 * Project 2
 * Authors: Trenton Smith, Junyu Chen
 *  
 */
#include "threads.h"

#define NUM_THREADS 10
int count = 0;
int thread_ints[NUM_THREADS];
TCB_t *runQ = 0;

void test1();
void test2();

void main(char** args) {

	TCB_t* threads[NUM_THREADS];

	printf("Initializing %d threads\n", NUM_THREADS);
	InitQueue(&runQ);
	int i = 0;
	for (i = 0; i < NUM_THREADS; i++) {
		start_thread(threads[i], (i%2 == 1) ? test1 : test2); 
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
		printf("test1 = Swapped %d : CurrentThread %d/%p : Visited %d \n", 
			count, count%NUM_THREADS, runQ, thread_ints[count%NUM_THREADS]);
		printf("i: %d\n", i);
		i++;
		puts("Swapping");
		count++;
		thread_ints[count%NUM_THREADS]++;
		yield();
		puts("SHOULD NOT PRINT");
	}
	puts("Loop end");
}

void test2() {
	int x = 0;
	while (count >= 0) {
		printf("test2 = Swapped %d : CurrentThread %d/%p : Visited %d \n", 
			count, count%NUM_THREADS, runQ, thread_ints[count%NUM_THREADS]);
		printf("x: %d\n", x);
		x++;
		puts("Swapping");
		count++;
		thread_ints[count%NUM_THREADS]++;
		yield();
		puts("SHOULD NOT PRINT");
	}
	puts("Loop end");
}
