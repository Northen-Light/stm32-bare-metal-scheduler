#include "systick.h"
#include "scheduler.h"

void systick_init(void) {
  SYST_CSR_REG = 0U;
  SYST_RVR_REG = 7999U;
  SYST_CVR_REG = 0U;

  SYST_CSR_REG |= SYST_CSR_TICKINT_BIT | SYST_CSR_CLKSOURCE_BIT | SYST_CSR_ENABLE_BIT;
}

void SysTick_Handler(void) {
  scheduler_yield();
}