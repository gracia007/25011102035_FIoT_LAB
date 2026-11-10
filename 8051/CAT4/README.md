# CAT4 - Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display

| Field | Details |
|---|---|
| **EXP** | CAT4 |
| **DATE** | 03/08/2026 |
| **NAME OF EXP** | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision, 4x4 matrix keypad, seven-segment display, 4 LEDs |
| **TASK NO** | Single task (no subdivisions in the questions PDF) |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Core Logic / Pseudocode / Code Base

**Working Principle:**

A 4x4 matrix keypad is scanned by driving one row LOW at a time and reading the columns. The detected key is shown on a seven-segment display through a lookup table, and the matching LED function is executed.

**Pseudocode:**

1. Initialise the LED, keypad and seven-segment ports.
2. `keypad_scan()`: drive each row LOW in turn and read the columns to find the pressed key.
3. Debounce the key and wait for release.
4. `display_digit(key)`: output the segment pattern from the lookup table.
5. `led_control(key)`: keys 1–4 turn ON LED1–LED4; 5 runs `running_led()`; 6 runs `alternate_led()`; 7 runs `binary_counter()`; 8 runs `blink_all()`; 9 turns all LEDs OFF; 0 resets the system.
6. Repeat the process continuously.

**Code Base:**

The program is split into the required functions: `keypad_scan`, `display_digit`, `led_control`, `running_led`, `binary_counter`, `alternate_led` and `blink_all`. A `seg_code[]` array stores the seven-segment patterns for digits 0–9.

## INFERENCE

Every valid key press is shown on the seven-segment display and triggers the matching LED operation. This demonstrates row/column keypad scanning, lookup-table based display driving and a modular function-based program structure.
