/* 
 * 
 * CSE 430 
 * Project 4
 * Authors: Trenton Smith, Junyu Chen
 * 
 * NOTE: Solution code is version 2 from lecture notes!
 *  
 */
#include "sem.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define READER_COUNT 3
#define WRITER_COUNT 2

TCB_t *runQ = 0;
SEM_t *mutex = 0, *rsem = 0, *wsem = 0;
int rwc = 0, rc = 0, wwc = 0, wc = 0, shared_int = 0;

void reader();
void reader_entry();
void reader_exit();
void writer();
void writer_entry();
void writer_exit();

void main(char** args) {
	TCB_t* threads[READER_COUNT + WRITER_COUNT];
	puts("initializing semaphores and threads");
	mutex = malloc(sizeof(SEM_t));
	rsem = malloc(sizeof(SEM_t));
	wsem = malloc(sizeof(SEM_t));
	InitSem(mutex, 1);
	InitSem(rsem, 0);
	InitSem(wsem, 0);
	InitQueue(&runQ);
	int i = 0, j = 0, h = 0;
	while (i < READER_COUNT + WRITER_COUNT) {	
		int r = rand() % 2;
		if (j < READER_COUNT && r == 0) {
			puts("Adding reader");
			start_thread(threads[i], reader);
			i++; j++;
		}
		if (h < WRITER_COUNT && r == 1) {
			puts("Adding writer");
			start_thread(threads[i], writer);
			i++; h++;
		}
	}
	srand(time(NULL));
	puts("runQ content:");
	printQueue(runQ);
	puts("\nstarting threads\n");
	run();
}

void reader() {
	puts("r");
	reader_entry();
	
	printf("Reader[%p]: %d\n", runQ, shared_int);
	sleep(1);
	
	reader_exit();
}

void reader_entry() {
	puts("r1");
	if (wwc > 0 || wc > 0) {
		rwc++;
		P(rsem);
		rwc--;
	}
	rc++;
	if (rwc > 0) {
		V(rsem);
	}
}

void reader_exit() {
	puts("r2");
	rc--;
	if (rc == 0 && wwc > 0) {
		V(wsem);
	}
	yield();
}

void writer() {
	puts("w");
	writer_entry();
	
	shared_int = rand();
	printf("Writer[%p]: %d\n", runQ, shared_int);
	sleep(1);
	
	writer_exit();
}

void writer_entry() {
	puts("w1");
	if (rc > 0 || wc > 0) {
		wwc++;
		P(wsem);
		wwc--;
	}
	wc++;
}

void writer_exit() {
	printf("w2 - wwc: %d rwc: %d\n", wwc, rwc);
	wc--;
	if (rwc > 0) {
		V(rsem);
	} 
	else if (wwc > 0) {
		V(wsem);
	}
	yield();
}
