#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

void scheduler_init(task_t *__tasks__, uint32_t __tasks_length__);
void scheduler_start(void);
void scheduler_yield(void);
void scheduler_tick(void);
void scheduler_next(void);

#endif