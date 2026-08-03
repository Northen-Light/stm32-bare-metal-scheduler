#ifndef SCHEDULER_INTERNAL_H
#define SCHEDULER_INTERNAL_H

#include "task.h"
extern tcb_t *current_tcb;

#ifdef USE_INTERNAL_SCHEDULER_SELECT_NEXT_TASK
void scheduler_select_next(void);
#endif

#endif