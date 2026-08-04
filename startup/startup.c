#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void main(void);

__attribute__((used, section(".isr_vector")))
const uintptr_t vector_table[] = {
  (uintptr_t) &_estack,
  (uintptr_t) Reset_Handler,
  0U,
  (uintptr_t) HardFault_Handler,
  0U,
  0U,
  0U,
  0U,
  0U,
  0U,
  0U,
  (uintptr_t) SVC_Handler,
  0U,
  0U,
  (uintptr_t) PendSV_Handler,
  (uintptr_t) SysTick_Handler,
};

void Reset_Handler(void) {
  uint32_t *start_data_sram = &_sdata;
  uint32_t *end_data_sram = &_edata;
  uint32_t *start_data_flash = &_sidata;

  while (start_data_sram != end_data_sram) {
    *start_data_sram++ = *start_data_flash++;
  }

  uint32_t *start_bss_sram = &_sbss;
  uint32_t *end_bss_sram = &_ebss;

  while (start_bss_sram != end_bss_sram) {
    *start_bss_sram++ = 0;
  }

  main();

  while (1) {}
}

void HardFault_Handler(void) {
  while (1) {}
}
