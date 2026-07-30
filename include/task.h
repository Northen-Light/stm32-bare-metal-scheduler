#ifndef TASK_H
#define TASK_H

#include <stdint.h>
typedef void (*task_function_t)(void);


typedef enum {
  TASK_READY,
  TASK_RUNNING,
  TASK_BLOCKED
} task_state_t;

typedef struct {
  uint32_t *sp;
  task_state_t task_state;
} tcb_t;

uint32_t *task_stack_init(uint32_t *stack_top, task_function_t task_function);

#endif