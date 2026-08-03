#include <stdint.h>
#include <stdbool.h>
#include "scheduler.h"
#include "task.h"
#include "systick.h"
#include "cortex_m.h"

#define MAX_TASKS                       10U
#define IDLE_STACK_WORDS                64U

tcb_t *current_tcb;

static tcb_t *tcb_table[MAX_TASKS];
static uint8_t tcb_index = 0;
static uint8_t tcb_count = 0;

static tcb_t tcb_idle;
static uint32_t task_idle_stack[IDLE_STACK_WORDS];
static void scheduler_create_idle_task(void);
static void idle_task_function(void);

void scheduler_start(void) {
  scheduler_create_idle_task();
  tcb_index++;
  current_tcb = tcb_table[tcb_index];
  current_tcb -> state = TASK_RUNNING;
  cortex_m_exception_priority_init();
  systick_init();
  cortex_m_start_first_task();
}

void scheduler_yield(void) {
  cortex_m_request_context_switch();
}

void scheduler_tick(void) {
  bool has_ready_tcb = false;

  for (uint8_t i = 1; i < tcb_count; i++) {
    if (tcb_table[i] -> state == TASK_BLOCKED) {

      (tcb_table[i] -> delay_ticks)--;
      if (tcb_table[i] -> delay_ticks == 0U) {
        tcb_table[i] -> state = TASK_READY;
      }
      if (tcb_table[i] -> state == TASK_READY) {
        has_ready_tcb = true;
      }
    }
  }

  if (has_ready_tcb) {
    scheduler_yield();
  }
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

  tcb_index = (uint8_t)(tcb_index + 1) % tcb_count;
  while (tcb_table[tcb_index] -> state != TASK_READY) {
    tcb_index = (uint8_t)(tcb_index + 1) % tcb_count;
  }
  current_tcb = tcb_table[tcb_index];
  current_tcb -> state = TASK_RUNNING;
}

static void scheduler_create_idle_task(void) {
  task_create(&tcb_idle, task_idle_stack + 64U, idle_task_function);
}

static void idle_task_function(void) {
  while (1) {
    __asm volatile("wfi");
  }
}