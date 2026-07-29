#ifndef CORTEX_M_H
#define CORTEX_M_H

#define INITIAL_XPSR                  (1U << 24U)
#define SCB_ICSR                      *((volatile uint32_t *) 0xE000ED04)

void cortex_m_start_first_task(void);
void cortex_m_set_pending_task_switch(void);

#endif