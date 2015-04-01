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
	if (sem->count > 0) {
		sem->count--;
	} else {
		RotQueue(&runQ);
		TCB_t *current = DelQueue(&runQ);
		AddQueue(&(sem->queue), current);
		if (runQ == NULL) {
			puts("\nrunQ empty");
			while (runQ == NULL) {
				sleep(1);
			}
		}
		int t = setcontext(&(runQ->context));
		if (t == -1) {
			puts("set error!");
			return;
		}
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
