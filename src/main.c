#include <stdint.h>
#include "task.h"
#include "scheduler.h"
              
#define TASK_STACK_WORDS                32U

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

    if (counter == 256U) {
      task_delay(5000U);
    }

    if (counter == 1024U) {
      counter = 0U;
    }
  }
}

void task_B_function(void) {
  while (1) {
    power = power * 2U;

    if (power > 4096U) {
      power = 1U;
      task_delay(5000U);
    }
  }
}

void task_C_function(void) {
  while (1) {
    for (uint32_t i = 0U; i < 1000U; i++) {
      sum += i;

      if (i == 500U) {
        task_delay(2000U);
      }
    }
    sum = 0U;
  }
}
void main(void) {
  task_create(&task_A, task_A_stack + TASK_STACK_WORDS, task_A_function);
  task_create(&task_B, task_B_stack + TASK_STACK_WORDS, task_B_function);
  task_create(&task_C, task_C_stack + TASK_STACK_WORDS, task_C_function);
  scheduler_start();

  while(1) {}
}