#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define RCC_APB2ENR                 *((volatile uint32_t *) 0x40021018U)
#define GPIOC_CRH                   *((volatile uint32_t *) 0x40011004U)
#define GPIOC_BSRR                  *((volatile uint32_t *) 0x40011010U)

void gpio_portA_init(void);
void gpioPA13_set(void);
void gpioPA13_reset(void);

#endif