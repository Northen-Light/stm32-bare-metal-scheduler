# STM32 Bare-Metal RTOS Kernel

A lightweight RTOS kernel built from scratch for the **STM32F103C8T6 (ARM Cortex-M3)** using register-level programming.

The project implements the core components of an RTOS kernel to demonstrate task scheduling, context switching, and task management without relying on an existing RTOS such as FreeRTOS.

---
# Project Structure

The kernel is organized into four modules:

- **task** — Task creation and task management
- **scheduler** — Scheduling algorithms
- **cortex_m** — Cortex-M specific functionality
- **systick** — System tick generation

---

# Features

- Task management
- Scheduler management
- Cooperative scheduling
- Preemptive round-robin scheduling
- PendSV-based context switching
- SVC-based first task startup
- Kernel-managed idle task

---

# Hardware

- STM32F103C8T6 (Blue Pill)
- ST-Link V2

---

# Project Goals

This project explores the internal implementation of an RTOS by building the kernel from scratch.

Topics covered include:

- ARM Cortex-M exception model
- Task scheduling
- Task state management
- Context switching
- Process Stack Pointer (PSP)
- PendSV
- SysTick
- Supervisor Calls (SVC)
- Critical sections
- RTOS kernel architecture

---

# Kernel Architecture

```
                     Application Tasks
                             │
                             ▼

              +-------------------------------+
              |         RTOS Kernel           |
              |-------------------------------|
              | task.c                        |
              | scheduler.c                   |
              | cortex_m.c                    |
              | systick.c                     |
              +---------------+---------------+
                              │
                              ▼

                 ARM Cortex-M3 Hardware
         (PendSV • SVC • SysTick • PSP • BASEPRI)
```

---

# Scheduling

## Cooperative Scheduling

The running task voluntarily yields the processor.

```
Task A
   │
task_yield()
   │
scheduler_yield()
   │
PendSV Pending
   │
PendSV Handler
   │
Save Context
   │
scheduler_select_next_tcb()
   │
Restore Context
   │
Task B
```

---

## Preemptive Round-Robin Scheduling

The SysTick interrupt periodically requests task rescheduling.

```
SysTick Interrupt
        │
scheduler_tick()
        │
scheduler_yield()
        │
PendSV Pending
        │
PendSV Handler
        │
Save Context
        │
scheduler_select_next_tcb()
        │
Restore Context
        │
Next READY Task
```

---

# Task State Transitions

```
                +------------+
                | TASK_READY |
                +------+-----+
                       |
           Scheduler selects task
                       |
                       ▼
               +--------------+
               | TASK_RUNNING |
               +------+-------+
                      |
          +-----------+------------+
          |                        |
 task_delay(...)   task_yield() / scheduler_yield()
          |                        |
          ▼                        ▼
   +--------------+         +------------+
   | TASK_BLOCKED |         | TASK_READY |
   +------+-------+         +------------+
          |
     Delay expires
          |
          ▼
   +------------+
   | TASK_READY |
   +------------+
```

---

# Context Switching

The kernel performs context switching using the **PendSV** exception.

During every context switch:

1. Hardware automatically **stacks** registers **R0–R3, R12, LR, PC, and xPSR**.
2. Save software-stacked registers **R4–R11**.
3. Store the current PSP in the current TCB.
4. Select the next READY task.
5. Load the PSP from the selected TCB.
6. Restore software-stacked registers **R4–R11**.
7. Hardware automatically **unstacks** registers **R0–R3, R12, LR, PC, and xPSR**.
8. Return to Thread Mode.

---

# Planned Features

- Priority-based scheduling
- Binary semaphores
- Mutexes
- Message queues
- Software timers
- Event flags
- Task suspend / resume

---

# Directory Structure

```text
stm32-bare-metal-rtos-kernel/
├── include/
│   ├── cortex_m.h
│   ├── gpio.h
│   ├── scheduler.h
│   ├── systick.h
│   └── task.h
│
├── linker/
│   └── main.ld
│
├── src/
│   ├── cortex_m.c
│   ├── gpio.c
│   ├── main.c
│   ├── scheduler.c
│   ├── scheduler_internal.h
│   ├── systick.c
│   └── task.c
│
├── startup/
│   └── startup.c
│
├── .gitignore
├── LICENSE
├── Makefile
└── README.md
```

---

# Learning Outcomes

This project provided practical experience with:

- ARM Cortex-M architecture
- Exception handling
- Context switching
- PendSV
- SysTick
- SVC
- PSP/MSP
- Task scheduling
- RTOS kernel design
- Modular firmware architecture

---

# Build

Build the firmware:

```bash
make
```

Flash the firmware:

```bash
make flash
```

---
# Development tools

- arm-none-eabi-gcc
- gdb
- GNU Make
- st-util
- ST-Link V2

---

# License

This project is licensed under the MIT License. See the `LICENSE` file for details.