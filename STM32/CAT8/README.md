# CAT8 – STM32 GPIO Bring-Up and Switch-Controlled LED

| Field | Details |
|---|---|
| **EXP** | CAT8 |
| **DATE** | 18/09/2026 |
| **NAME OF EXP** | STM32 GPIO Bring-Up and Switch-Controlled LED |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 Blue Pill (ARM Cortex-M3, 72 MHz), ST-Link V2, STM32CubeMX + Keil MDK-ARM (HAL), LED, push-button |
| **TASK NO** | Task 8A – GPIO Input/Output, Task 8B – Event-Based Control, Task 8C – Short Press vs Long Press |

## Overview

Bring up the STM32 toolchain (CubeMX + Keil MDK) and interface a push-button and LED using HAL GPIO functions. The tasks progress from level-based control, to event-based toggling with debouncing, to classifying short and long presses without blocking delays.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task 8A – GPIO Input/Output | [`TASKA_GPIO_Input_Output/`](TASKA_GPIO_Input_Output/) | LED follows the switch state |
| Task 8B – Event-Based Control | [`TASKB_Event_Based_Control/`](TASKB_Event_Based_Control/) | Each valid press toggles the LED (debounced) |
| Task 8C – Short Press vs Long Press | [`TASKC_Short_vs_Long_Press/`](TASKC_Short_vs_Long_Press/) | < 1 s toggles, ≥ 1 s enters blinking mode, non-blocking |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
