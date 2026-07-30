#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

void scheduler_init(tcb_t *first, tcb_t *second, tcb_t *third);
void scheduler_start(void);
void scheduler_schedule_next(void);

#endif