/* 
 * 
 * CSE 430 
 * Project 3
 * Authors: Trenton Smith, Junyu Chen
 *  
 */
#include "sem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define BUFFER_SIZE 5

TCB_t *runQ = 0;
SEM_t *cs_sem = 0, *full_sem = 0, *empty_sem = 0;
int buffer[BUFFER_SIZE];
int method1_count = 0, in = 0, out = 0;

void producer();
void consumer();
void method1();
void method1_1();
void method2();

void main(char** args) {
	//uncomment method1(); to run method 1 test
	//method1();	
	
	//uncomment method2(); to run method 2 test
	method2();
}

void producer() {
	P(empty_sem);
	buffer[in] = rand();
	printf("%p produced: %d at buffer[%d]\n", runQ, buffer[in], in);
	sleep(1);
	in = (in+1) % BUFFER_SIZE;
	V(full_sem);
}

void consumer() {
	P(full_sem);
	printf("%p consumed: %d at buffer[%d]\n", runQ, buffer[out], out);
	buffer[out] = -1;
	sleep(1);
	out = (out+1) % BUFFER_SIZE;
	V(empty_sem);
}

void method1() {
	TCB_t* threads[10];
	puts("initializing semaphore and threads");
	cs_sem = malloc(sizeof(SEM_t));
	InitSem(cs_sem, 1);
	InitQueue(&runQ);	
	int i = 0;
	while (i < 10) {
		start_thread(threads[i], method1_1);
		i++;
	}	
	puts("runQ content: ");
	printQueue(runQ);
	puts("\nstarting threads\n");
	run();
}

void method1_1() {
	int y = 0;
	while (y >= 0) {		
		printf("thread: %p\n", runQ);
		puts("attempting entry");
		P(cs_sem);
		puts("entered");
		printf("method1_count: %d\n", method1_count++);
		printf("y: %d\n", y++);
		sleep(1);
		V(cs_sem);
		puts("cs end");
		sleep(1);
	}
}

void method2() {
	TCB_t* threads[4];
	puts("initializing semaphores and threads");
	full_sem = malloc(sizeof(SEM_t));
	empty_sem = malloc(sizeof(SEM_t));
	InitSem(full_sem, 0);
	InitSem(empty_sem, BUFFER_SIZE);
	InitQueue(&runQ);	
	int i = 0;
	while (i < 4) {
		start_thread(threads[i], i >= 2 ? producer : consumer);
		i++;
	}	
	srand(time(NULL));
	puts("runQ content:");
	printQueue(runQ);
	puts("\nstarting threads\n");
	run();
}
