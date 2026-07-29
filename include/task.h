#ifndef TASK_H
#define TASK_H

#include <stdint.h>
typedef void (*task_function_t)(void);

typedef struct {
  uint32_t *sp;
} task_t;

uint32_t *task_stack_init(uint32_t *stack_top, task_function_t task_function);

#endif