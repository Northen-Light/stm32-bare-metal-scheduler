#include <stdint.h>
#include "scheduler.h"
#include "task.h"
#include "systick.h"
#include "cortex_m.h"

tcb_t *current_tcb;

static tcb_t *tcb_table[MAX_TASKS];
static uint32_t tcb_index = 0;
static uint32_t tcb_count = 0;

void scheduler_start(void) {
  current_tcb = tcb_table[0];
  current_tcb -> state = TASK_RUNNING;
  cortex_m_exception_priority_init();
  systick_init();
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  cortex_m_request_context_switch();
}

void scheduler_tick(void) {
  for (uint8_t i = 0; i < tcb_count; i++) {
    if (tcb_table[i] -> state == TASK_BLOCKED) {
      (tcb_table[i] -> delay_ticks)--;
      if (tcb_table[i] -> delay_ticks == 0U) {
        tcb_table[i] -> state = TASK_READY;
      }
    }
  }
  scheduler_yield();
}

void scheduler_add_tcb(tcb_t *tcb) {
  if (tcb_count >= MAX_TASKS) {
    return;
  }
  tcb_table[tcb_count++] = tcb;
}

void scheduler_select_next(void) {
  if (current_tcb -> state == TASK_RUNNING) {
    current_tcb -> state = TASK_READY;
  }
  tcb_index = (tcb_index + 1U) % tcb_count;
  while (tcb_table[tcb_index] -> state != TASK_READY) {
    tcb_index = (tcb_index + 1U) % tcb_count;
  }
  current_tcb = tcb_table[tcb_index];
  current_tcb -> state = TASK_RUNNING;
}