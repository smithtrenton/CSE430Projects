#ifndef SEM_HEADER
#define SEM_HEADER
#include "threads.h"
#include <unistd.h>

typedef struct SEM_t {
     struct TCB_t   *queue;
     int			value;
} SEM_t;

void InitSem(SEM_t* sem, int v) {
	sem->queue = NULL;
	sem->value = v;
}

void P(SEM_t* sem) {
	sem->value--;
	if (sem->value < 0) {
		puts("blocking");
		TCB_t *current = DelQueue(&runQ);
		AddQueue(&(sem->queue), current);
		puts("sem->queue:");
		printQueue(sem->queue);
		if (runQ == NULL) {
			puts("runQ empty");
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
	sem->value++;
	if (sem->value <= 0) {
		puts("unblocking");
		AddQueue(&runQ, DelQueue(&(sem->queue)));
		puts("sem->queue:");
		printQueue(sem->queue);
	}
	yield();
}

#endif
