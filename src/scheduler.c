#include "scheduler.h"
#include "task.h"
#include "cortex_m.h"

task_t *__task_A__;
task_t *__task_B__;
task_t *__task_C__;
task_t *cur;
task_t *next;
uint8_t count = 0;

void scheduler_init(task_t *first, task_t *second, task_t *third) {
  __task_A__ = first;
  __task_B__ = second;
  __task_C__ = third;
}

void scheduler_start(void) {
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  switch (count) {
    case 0 : {
      cur = __task_A__;
      next = __task_B__;
      break;
    }
    
    case 1 : {
      cur = __task_B__;
      next = __task_C__;
      break;
    }

    case 2 : {
      cur = __task_C__;
      next = __task_A__;
      break;
    }

    default : {}
  }
  count = (count + (uint8_t)1) % (uint8_t)3;
  cortex_m_set_pending_task_switch();
}