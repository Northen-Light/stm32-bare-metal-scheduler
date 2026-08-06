#ifndef SCHEDULER_INTERNAL_H
#define SCHEDULER_INTERNAL_H

#include "task.h"

extern tcb_t *current_tcb;
void scheduler_select_next_task(void);

#endif