#ifndef CORTEX_M_H
#define CORTEX_M_H

#define SCB_ICSR_REG                  *((volatile uint32_t *) 0xE000ED04U)

#define INITIAL_XPSR                  (1U << 24U)

void cortex_m_start_first_task(void);
void cortex_m_set_pending_task_switch(void);

#endif