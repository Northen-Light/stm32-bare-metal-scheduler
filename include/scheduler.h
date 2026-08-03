#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

void scheduler_start(void);
void scheduler_yield(void);
void scheduler_tick(void);
void scheduler_add_tcb(tcb_t *tcb);

#endif