#ifndef CORTEX_M_H
#define CORTEX_M_H


#define SCB_ICSR_REG                            *((volatile uint32_t *) 0xE000ED04U)
#define SCB_SHPR3_REG                           *((volatile uint32_t *) 0xE000ED20U)

#define __NVIC_PRO_BITS__                       4U
#define SCB_SHPR_PENDSV_PRIORITY                15U
#define SCB_SHPR_SYSTICK_PRIORITY               14U
#define BASEPRI_MASK_PRIORITY                   5U
#define INITIAL_XPSR                            (1U << 24U)

#define SCB_ICSR_PENDSV_BIT                     (1U << 28U)

#define PRIORITY_ENCODE(priority)               ((uint32_t)priority << (8U - __NVIC_PRO_BITS__))

#define SCB_SHPR_PENDSV_PRIORITY_VALUE          (PRIORITY_ENCODE(15U) << 16U)
#define SCB_SHPR_SYSTICK_PRIORITY_VALUE         (PRIORITY_ENCODE(14U) << 24U)
#define BASEPRI_MASK_PRIORITY_VALUE             PRIORITY_ENCODE(BASEPRI_MASK_PRIORITY)

void cortex_m_start_first_task(void);
void cortex_m_set_pending_task_switch(void);
void cortex_m_exception_priority_init(void);

#endif