#ifndef CORTEX_M_H
#define CORTEX_M_H

#define SCB_ICSR_REG                  *((volatile uint32_t *) 0xE000ED04U)
#define SCB_SHPR3_REG                 *((volatile uint32_t *) 0xE000ED20U)

#define SCB_ICSR_PENDSV_BIT           (1U << 28U)

#define SCB_SHPR_PENDSV_BIT_FIELD     (0xFFU << 16U)
#define SCB_SHPR_SYSTICK_BIT_FIELD    (0xFEU << 24U)

#define INITIAL_XPSR                  (1U << 24U)

void cortex_m_start_first_task(void);
void cortex_m_set_pending_task_switch(void);
void cortex_m_exception_priority_init(void);

#endif