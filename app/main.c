#include <stdint.h>

#define INITIAL_XPSR                  (1U << 24U)
#define EXEC_RETURN_TO_PSP            0xFFFFFFFDU

__attribute__((aligned(8)))
uint32_t taskA_stack[256];

typedef void (*task_function_t)(void);

typedef struct {
  uint32_t *stack_pointer
} task_t;

task_t taskA;

volatile uint32_t counter = 0;

void task_exit_error(void) {
  while(1);
}

void taskA_function(void) {
  while(1) {
    counter++;
    if (counter == 10000)
      counter = 0;
  }
}

uint32_t *task_stack_initisation(uint32_t *stack_top, task_function_t task_function) {
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

int main(void) {
  taskA.stack_pointer = task_stack_initisation(taskA_stack + 256, taskA_function);
  __asm volatile("svc #0");
  while(1);
  return 0;
}

__attribute((naked))
void SVC_Handler(void) {
  __asm volatile(
    "ldr r2, =taskA               \n"
    "ldr r0, [r2]                 \n"
    "ldmia r0!, {r4-r11}          \n"
    "msr psp, r0                  \n"
    "isb                          \n"
    "ldr r0, =0xFFFFFFFDU         \n"
    "mov r14, r0                  \n"
    "bx r14                       \n"
  );
}