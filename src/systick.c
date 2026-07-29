#include "systick.h"
#include "scheduler.h"

void systick_init(void) {
  SYST_RVR_REG = 7999U;

  SYST_CSR_REG &= ~SYST_CSR_ENABLE_BIT;
  SYST_CSR_REG |= SYST_CSR_TICKINT_BIT;
  SYST_CSR_REG |= SYST_CSR_ENABLE_BIT;
}

void Systick_Handler(void) {
  scheduler_yield();
}