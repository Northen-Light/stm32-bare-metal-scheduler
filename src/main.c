#include <stdint.h>
#include "task.h"
#include "scheduler.h"
#include "systick.h"
#include "cortex_m.h"

#define TASK_STACK_WORDS                256U

tcb_t task_A;
tcb_t task_B;
tcb_t task_C;

__attribute__((aligned(8U)))
uint32_t task_A_stack[TASK_STACK_WORDS];

__attribute__((aligned(8U)))
uint32_t task_B_stack[TASK_STACK_WORDS];

__attribute__((aligned(8U)))
uint32_t task_C_stack[TASK_STACK_WORDS];

uint32_t counter = 0U;
uint32_t power = 1U;
uint32_t sum = 0U; 

void task_A_function(void) {
  while(1) {
    counter++;
    if (counter == 0x400U) {
      counter = 0U;
    }
  }
}

void task_B_function(void) {
  while (1) {
    power = power * 2U;
    if (power > 0x1000U) {
      power = 1U;
    }
  }
}

void task_C_function(void) {
  while (1) {
    for (uint32_t i = 0U; i < 1000U; i++) {
      sum += i;
    }
    sum = 0U;
  }
}
int main(void) {
  task_A.sp = task_stack_init(task_A_stack + TASK_STACK_WORDS, task_A_function);
  task_A.task_state = TASK_READY;

  task_B.sp = task_stack_init(task_B_stack + TASK_STACK_WORDS, task_B_function);
  task_B.task_state = TASK_READY;

  task_C.sp = task_stack_init(task_C_stack + TASK_STACK_WORDS, task_C_function);
  task_C.task_state = TASK_READY;

  scheduler_init(&task_A, &task_B, &task_C);
  cortex_m_exception_priority_init();
  systick_init();
  cortex_m_start_first_task();

  while(1);
  return 0;
}