#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

void scheduler_init(task_t *first, task_t *second, task_t *third);
void scheduler_start(void);
void scheduler_yield(void);

#endif