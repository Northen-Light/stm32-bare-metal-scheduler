#include "cortex_m.h"
#include "task.h"
#include "scheduler_internal.h"

void cortex_m_request_first_task_start(void) {
  __asm volatile("svc #0");
}

void cortex_m_request_context_switch(void) {
  SCB_ICSR_REG = SCB_ICSR_PENDSV_BIT;
}

void cortex_m_exception_priority_init(void) {
  SCB_SHPR3_REG = SCB_SHPR_PENDSV_PRIORITY_VALUE | SCB_SHPR_SYSTICK_PRIORITY_VALUE;
}

__attribute((naked))
void SVC_Handler(void) {
  __asm volatile(
    "ldr r3, =current_tcb         \n"
    "ldr r2, [r3]                 \n"
    "ldr r0, [r2]                 \n"
    "ldmia r0!, {r4-r11}          \n"
    "msr psp, r0                  \n"
    "isb                          \n"
    "mov r14, 0xFFFFFFFDU         \n"
    "bx r14                       \n"
  );
}

__attribute((naked))  
void PendSV_Handler(void) {
  __asm volatile(
    "mrs r0, psp                  \n"
    "stmdb r0!, {r4-r11}          \n"
    "ldr r3, =current_tcb         \n"
    "ldr r2, [r3]                 \n"
    "str r0, [r2]                 \n"
    "                             \n"
    "stmdb sp!, {r3, r14}         \n"
    "mov r0, %0                   \n"
    "msr basepri, r0              \n"
    "bl scheduler_select_next_tcb\n"
    "mov r0, #0                   \n"
    "msr basepri, r0              \n"
    "ldmia sp!, {r3, r14}         \n"
    "                             \n"
    "ldr r2, [r3]                 \n"
    "ldr r0, [r2]                 \n"
    "ldmia r0!, {r4-r11}          \n"
    "msr psp, r0                  \n"
    "isb                          \n"
    "bx r14                       \n"
    ::"i"(BASEPRI_MASK_PRIORITY_VALUE)
  );
}