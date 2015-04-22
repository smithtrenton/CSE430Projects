/* 
 * 
 * CSE 430 
 * Project 4
 * Authors: Trenton Smith, Junyu Chen
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
	while (1 > 0) {
		//printf("Reader[%p]: Start\n", runQ);
		reader_entry();
		//printf("Reader[%p]: Entered\n", runQ);
		
		P(mutex);
		printf("Reader[%p]: %d\n", runQ, shared_int);
		sleep(1);
		V(mutex);
		
		//printf("Reader[%p]: Exiting\n", runQ);
		reader_exit();
		//printf("Reader[%p]: Exit\n", runQ);
	}
}

void reader_entry() {
	P(mutex);
	if (wwc > 0 || wc > 0) {
		rwc++;
		V(mutex);
		//printf("Reader[%p]: Adding to wait queue\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
		P(rsem);
		rwc--;
		//printf("Reader[%p]: Returned from wait queue\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
	}
	rc++;
	if (rwc > 0) {
		//printf("Reader[%p]: Releasing a reader\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
		V(rsem);
	} else {
		V(mutex);
	}
}

void reader_exit() {
	P(mutex);
	rc--;
	if (rc == 0 && wwc > 0) {
		//printf("Reader[%p]: Releasing a writer\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
		V(wsem);
	} else {
		V(mutex);
	}
}

void writer() {
	while (1 > 0) {
		//printf("Writer[%p]: Start\n", runQ);
		writer_entry();
		//printf("Writer[%p]: Entered\n", runQ);
		
		P(mutex);
		shared_int = rand();
		printf("Writer[%p]: %d\n", runQ, shared_int);
		sleep(1);
		V(mutex);
		
		//printf("Writer[%p]: Exiting\n", runQ);
		writer_exit();
		//printf("Writer[%p]: Exit\n", runQ);
	}
}

void writer_entry() {
	P(mutex);
	if (rc > 0 || wc > 0) {
		wwc++;
		V(mutex);
		//printf("Writer[%p]: Adding to wait queue\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
		P(wsem);
		wwc--;
		//printf("Writer[%p]: Returned from wait queue\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
	}
	wc++;
	V(mutex);
}

void writer_exit() {
	P(mutex);
	wc--;
	if (rwc > 0) {
		//printf("Writer[%p]: Releasing a reader\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
		V(rsem);
	}
	else if (wwc > 0) {
		//printf("Writer[%p]: Releasing a writer\n", runQ);
		//printf("\t(wwc:%d, wc:%d, rwc:%d, rc:%d)\n", wwc, wc, rwc, rc);
		V(wsem);
	}
}
