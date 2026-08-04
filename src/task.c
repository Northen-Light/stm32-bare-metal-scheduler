#include "task.h"
#include "cortex_m.h"
#include "scheduler.h"
#include "scheduler_internal.h"

static void task_exit_error(void);
static uint32_t *task_stack_init(uint32_t *stack_top, task_function_t task_function);

void task_create(tcb_t *tcb, uint32_t *stack_top, task_function_t task_function) {
  tcb -> sp = task_stack_init(stack_top, task_function);
  tcb -> state = TASK_READY;
  scheduler_add_tcb(tcb);
};

void task_yield(void) {
  scheduler_yield();
}

void task_delay(uint32_t ticks) {
  current_tcb -> state = TASK_BLOCKED;
  current_tcb -> delay_ticks = ticks;
  task_yield();
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
  while(1) {}
}