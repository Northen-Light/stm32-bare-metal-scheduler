#include "gpio.h"

void gpio_portA_init(void) {
  RCC_APB2ENR |= (1U << 4U);
  GPIOC_CRH &= ~(0xFU << 20U);
  GPIOC_CRH |= (1U << 20U);
}

void gpioPA13_set() {
  GPIOC_BSRR = (1U << 13U);
}

void gpioPA13_reset() {
  GPIOC_BSRR = (1U << (13U + 16U));
}