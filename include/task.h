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
  task_state_t state;
  uint32_t delay_ticks;
} task_t;

void task_create(task_t *task, uint32_t *stack_top, task_function_t task_function);
void task_delay(task_t *task, uint32_t ticks);

#endif