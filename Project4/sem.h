#ifndef SEM_HEADER
#define SEM_HEADER
#include "threads.h"
#include <unistd.h>

typedef struct SEM_t {
     struct TCB_t   *queue;
     int			count;
} SEM_t;

void InitSem(SEM_t* sem, int c) {
	sem->queue = NULL;
	sem->count = c;
}

void P(SEM_t* sem) {
	sem->count--;
	if (sem->count < 0) {
		RotQueue(&runQ);
		TCB_t *current = DelQueue(&runQ);
		AddQueue(&(sem->queue), current);
		if (runQ == NULL) {
			puts("\nrunQ empty");
			while (runQ == NULL) {
				sleep(1);
			}
		}
		swapcontext(&(current->context), &(runQ->context));
	}
}

void V(SEM_t* sem) {
	sem->count++;
	if (sem->queue != NULL) {
		RotQueue(&(sem->queue));
		AddQueue(&runQ, DelQueue(&(sem->queue)));
	}
	yield();
}

#endif
