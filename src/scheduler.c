#include "scheduler.h"
#include "task.h"
#include "cortex_m.h"

task_t *__task_A__;
task_t *__task_B__;
task_t *cur;
task_t *next;
uint8_t count = 0;

void scheduler_init(task_t *first, task_t *second) {
  __task_A__ = first;
  __task_B__ = second;
}

void scheduler_start(void) {
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  if (count == 0) {
    cur = __task_A__;
    next = __task_B__;
  } else {
    cur = __task_B__;
    next = __task_A__;
  }
  count ^= 1;
  cortex_m_set_pending_task_switch();
}