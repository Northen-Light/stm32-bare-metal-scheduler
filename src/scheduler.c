#include "scheduler.h"
#include "task.h"
#include "cortex_m.h"

static task_t *tasks[3];
static uint8_t count = 0;
task_t *current_task;
task_t *next_task;

void scheduler_init(task_t *first, task_t *second, task_t *third) {
  tasks[0] = first;
  tasks[1] = second;
  tasks[2] = third;
  
  current_task = tasks[0];
  next_task = tasks[0];
}

void scheduler_start(void) {
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  current_task = next_task;
  count = (uint8_t)((count + 1) % 3);
  next_task = tasks[count];
  cortex_m_set_pending_task_switch();
}