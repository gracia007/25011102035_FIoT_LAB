# CAT12 – STM32F401RE Cortex-M4: GPIO and User Input Programming

| Field | Details |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 14/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4F, up to 84 MHz), on-board ST-Link, STM32CubeMX + Keil MDK-ARM (HAL), on-board LED LD2 and user button B1 |
| **TASK NO** | Task 1 – On-board LED Bring-Up, Task 2 – On-board Switch Control with State Remembrance, Task 3 – Short-Press and Long-Press Detection |

## Overview

Bring up the NUCLEO-F401RE (ARM Cortex-M4) board. Prerequisites: observe the on-board oscillator frequency, study the STM32F401RE specifications (clock frequency, GPIO groups, number of UARTs, I²Cs, SPIs), decide the clock configuration in CubeMX and refer to the Nucleo-64 pinout (UM1724). The tasks then cover LED output, button control with state remembrance, and short/long press detection.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task 1 – On-board LED Bring-Up | [`TASKA_Onboard_LED_Bring_Up/`](TASKA_Onboard_LED_Bring_Up/) | Blink LD2 at a fixed interval to verify hardware and GPIO |
| Task 2 – On-board Switch Control with State Remembrance | [`TASKB_Switch_Control_State_Remembrance/`](TASKB_Switch_Control_State_Remembrance/) | B1 toggles LD2; LED keeps its state after release |
| Task 3 – Short-Press and Long-Press Detection | [`TASKC_Short_and_Long_Press_Detection/`](TASKC_Short_and_Long_Press_Detection/) | Different actions for short and long presses of B1 |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
