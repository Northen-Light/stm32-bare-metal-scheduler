#include "cortex_m.h"
#include "task.h"

extern task_t *cur;
extern task_t *next;

void cortex_m_start_first_task(void) {
  __asm volatile("svc #0");
}

void cortex_m_set_pending_task_switch(void) {
  SCB_ICSR_REG |= (1U << 28U);
}

__attribute((naked))
void SVC_Handler(void) {
  __asm volatile(
    "ldr r3, =__task_A__          \n"
    "ldr r2, [r3]                 \n"
    "ldr r0, [r2]                 \n"
    "ldmia r0!, {r4-r11}          \n"
    "msr psp, r0                  \n"
    "isb                          \n"
    "ldr r0, =0xFFFFFFFDU         \n"
    "mov r14, r0                  \n"
    "bx r14                       \n"
    "                             \n"
    ".ltorg                       \n"
  );
}

__attribute((naked))
void PendSV_Handler(void) {
  __asm volatile(
    "mrs r0, psp                  \n"
    "stmdb r0!, {r4-r11}          \n"
    "ldr r3, =cur                 \n"
    "ldr r2, [r3]                 \n"
    "str r0, [r2]                 \n"
    "                             \n"
    "ldr r3, =next                \n"
    "ldr r2, [r3]                 \n"
    "ldr r0, [r2]                 \n"
    "ldmia r0!, {r4-r11}          \n"
    "msr psp, r0                  \n"
    "isb                          \n"
    "ldr r0, =0xFFFFFFFDU         \n"
    "mov r14, r0                  \n"
    "bx r14                       \n"
  );
}