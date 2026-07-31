#include "scheduler.h"
#include "task.h"
#include "systick.h"
#include "cortex_m.h"

static tcb_t *tasks[3];
static uint8_t count = 0;
tcb_t *current_task;

void scheduler_init(tcb_t *first, tcb_t *second, tcb_t *third) {
  tasks[0] = first;
  tasks[1] = second;
  tasks[2] = third;
}

void scheduler_start(void) {
  current_task = tasks[0];
  current_task -> task_state = TASK_RUNNING;
  cortex_m_exception_priority_init();
  systick_init();
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  cortex_m_set_pending_task_switch();
}

void scheduler_schedule_next(void) {
  current_task -> task_state = TASK_READY;
  count = (uint8_t)((count + 1) % 3);
  current_task = tasks[count];
  current_task -> task_state = TASK_RUNNING;
}