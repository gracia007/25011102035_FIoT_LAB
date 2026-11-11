# CAT2 – 8051 Tool Chain Setup – Development Board – AT89S52 (GPIO Interfacing)

| Field | Details |
|---|---|
| **EXP** | CAT2 |
| **DATE** | 20/07/2026 |
| **NAME OF EXP** | 8051 Tool Chain Setup – Development Board – AT89S52 (GPIO Interfacing) |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, on-board user LED |
| **TASK NO** | Task 1 – Hardware Board Bring-Up, Task 2 – Bare-Metal LED Blink, Task 3 – Customised Library Function for Delay |

## Overview

Bring up the AT89S52 development board, then compile a minimal bare-metal C program, program the device and control an LED by directly accessing the microcontroller's memory-mapped GPIO registers. Arduino APIs, HAL libraries and RTOS services are not used.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task 1 – Hardware Board Bring-Up | [`TASKA_Hardware_Board_Bring_Up/`](TASKA_Hardware_Board_Bring_Up/) | Identify MCU, programmer, power, LED pin; verify rails; establish host–target link |
| Task 2 – Bare-Metal LED Blink | [`TASKB_Bare_Metal_LED_Blink/`](TASKB_Bare_Metal_LED_Blink/) | Configure the LED GPIO by direct register access and blink at ≈ 1 Hz |
| Task 3 – Customised Library Function for Delay | [`TASKC_Custom_Delay_Library/`](TASKC_Custom_Delay_Library/) | Reusable `delay_ms()` library (delay.h / delay.c) |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
