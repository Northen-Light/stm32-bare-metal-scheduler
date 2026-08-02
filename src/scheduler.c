#include <stdbool.h>
#include "scheduler.h"
#include "task.h"
#include "systick.h"
#include "cortex_m.h"

task_t *tasks;
task_t *current_task;
uint32_t tasks_length;

static uint32_t count = 0;

void scheduler_init(task_t *__tasks__, uint32_t __tasks_length__) {
  tasks = __tasks__;
  tasks_length = __tasks_length__;
}

void scheduler_start(void) {
  current_task = &tasks[0];
  current_task -> state = TASK_RUNNING;
  cortex_m_exception_priority_init();
  systick_init();
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  cortex_m_set_pending_task_switch();
}

void scheduler_tick(void) {
  for (uint8_t i = 0; i < tasks_length; i++) {
    if (tasks[i].state == TASK_BLOCKED) {
      (tasks[i].delay_ticks)--;
      if (tasks[i].delay_ticks == 0U) {
        tasks[i].state = TASK_READY;
      }
    }
  }
  scheduler_yield();
}

void scheduler_next(void) {
  if (current_task -> state == TASK_RUNNING) {
    current_task -> state = TASK_READY;
  }
  count = (count + 1U) % tasks_length;
  while (tasks[count].state != TASK_READY) {
    count = (count + 1U) % tasks_length;
  }
  current_task = &tasks[count];
  current_task -> state = TASK_RUNNING;
}