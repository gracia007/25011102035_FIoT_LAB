# CAT7 – 16x2 LCD Driver Development and Dynamic Display Control

| Field | Details |
|---|---|
| **EXP** | CAT7 |
| **DATE** | 24/08/2026 |
| **NAME OF EXP** | 16x2 LCD Driver Development and Dynamic Display Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, 16x2 HD44780-compatible LCD (4-bit mode), 10 kΩ contrast potentiometer, 4x4 keypad |
| **TASK NO** | Task 7A – LCD Initialization and Character/String Display, Task 7B – Cursor Positioning and Dynamic Value Update, Task 7C – 4x4 Keypad-Based Character Movement |

## Overview

Develop an Embedded C LCD driver for the AT89S52 that initialises a 16x2 character LCD, positions the cursor, displays characters and strings, updates values and clears the display. The command sequence is derived from the HD44780 datasheet. The key outcome is learning how to read a peripheral datasheet, identify command fields, derive command values, implement a low-level driver and validate it on hardware.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task 7A – LCD Initialization and Character/String Display | [`TASK7A/`](TASK7A/) | 4-bit driver: lcd_init(), lcd_cmd(), lcd_data(); text on both rows |
| Task 7B – Cursor Positioning and Dynamic Value Update | [`TASK7B/`](TASK7B/) | lcd_goto(), lcd_puts(), lcd_print_number() for live values |
| Task 7C – 4x4 Keypad-Based Character Movement | [`TASK7C/`](TASK7C/) | Move a character on the 16x2 display with keys 2/8/4/6 |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
