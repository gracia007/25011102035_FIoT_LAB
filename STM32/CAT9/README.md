# CAT9 – STM32 UART Command Controlled LED

| Field | Details |
|---|---|
| **EXP** | CAT9 |
| **DATE** | 28/09/2026 |
| **NAME OF EXP** | STM32 UART Command Controlled LED |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 Blue Pill (ARM Cortex-M3, 72 MHz), ST-Link V2, STM32CubeMX + Keil MDK-ARM (HAL), USB-to-TTL serial converter, PC with PuTTY |
| **TASK NO** | Task 9A – Basic UART Communication, Task 9B – String-Based Application Logic |

## Overview

Configure the STM32 UART using CubeMX and HAL, establish communication with a PC terminal, and build a string-based command interface that controls the on-board LED. The effect of carriage return (\r) and line feed (\n) on the terminal is also investigated.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task 9A – Basic UART Communication | [`TASKA_Basic_UART_Communication/`](TASKA_Basic_UART_Communication/) | Transmit a character repeatedly, then receive and echo; CR/LF tests |
| Task 9B – String-Based Application Logic | [`TASKB_String_Based_Application_Logic/`](TASKB_String_Based_Application_Logic/) | Command interface: LED ON / LED OFF / LED TOGGLE |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
