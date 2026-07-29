#include <stdint.h>
#include <stdbool.h>
#include "task.h"
#include "scheduler.h"
#include "systick.h"

task_t task_A;
task_t task_B;
task_t task_C;

__attribute__((aligned(8U)))
uint32_t task_A_stack[256U];

__attribute__((aligned(8U)))
uint32_t task_B_stack[256U];

__attribute__((aligned(8U)))
uint32_t task_C_stack[256U];

uint32_t counter = 0U;
uint32_t pow = 1U;
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
    pow = pow * 2U;
    if (pow > 0x1000U) {
      pow = 1U;
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
  task_A.sp = task_stack_init(task_A_stack + 256, task_A_function);
  task_B.sp = task_stack_init(task_B_stack + 256, task_B_function);
  task_C.sp = task_stack_init(task_C_stack + 256, task_C_function);

  scheduler_init(&task_A, &task_B, &task_C);
  systick_init();
  scheduler_start();

  while(1);
  return 0;
}