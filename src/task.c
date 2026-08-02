#include "task.h"
#include "cortex_m.h"
#include "scheduler.h"

static void task_exit_error(void);
static uint32_t *task_stack_init(uint32_t *stack_top, task_function_t task_function);

void task_create(task_t *task, uint32_t *stack_top, task_function_t task_function) {
  task -> sp = task_stack_init(stack_top, task_function);
  task -> state = TASK_READY;
};

void task_delay(task_t *task, uint32_t ticks) {
  task -> state = TASK_BLOCKED;
  task -> delay_ticks = ticks;
  scheduler_yield();
}

static uint32_t *task_stack_init(uint32_t *stack_top, task_function_t task_function) {
  uint32_t *sp = stack_top;
  *(--sp) = INITIAL_XPSR;                   // XPSR
  *(--sp) = (uint32_t) task_function;       // PC
  *(--sp) = (uint32_t) task_exit_error;     // LR
  *(--sp) = 0;                              // R12
  *(--sp) = 0;                              // R3
  *(--sp) = 0;                              // R2
  *(--sp) = 0;                              // R1
  *(--sp) = 0;                              // R0

  *(--sp) = 0;                              // R11
  *(--sp) = 0;                              // R10
  *(--sp) = 0;                              // R9
  *(--sp) = 0;                              // R8
  *(--sp) = 0;                              // R7
  *(--sp) = 0;                              // R6
  *(--sp) = 0;                              // R5
  *(--sp) = 0;                              // R4

  return sp;
}
static void task_exit_error(void) {
  while(1);
}