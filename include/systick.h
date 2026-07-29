#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

#define SYST_CSR_REG                   *((volatile uint32_t *) 0xE000E010U)
#define SYST_RVR_REG                   *((volatile uint32_t *) 0xE000E014U)

#define SYST_CSR_ENABLE_BIT            (1U << 0U)
#define SYST_CSR_TICKINT_BIT           (1U << 1U)

void systick_init(void);

#endif