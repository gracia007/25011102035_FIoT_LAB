# CAT7 – Task 7B – Cursor Positioning and Dynamic Value Update

| Field | Details |
|---|---|
| **EXP** | CAT7 |
| **DATE** | 24/08/2026 |
| **NAME OF EXP** | 16x2 LCD Driver Development and Dynamic Display Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, 16x2 HD44780-compatible LCD (4-bit mode), 10 kΩ contrast potentiometer, 4x4 keypad |
| **TASK NO** | Task 7B – Cursor Positioning and Dynamic Value Update |

## 1. Objective

Develop LCD cursor-positioning and data-update functions: `lcd_goto(row, column)`, `lcd_puts(string)` and `lcd_print_number(value)`.

## 2. Circuit Diagram

<img width="1600" height="1066" alt="WhatsApp Image 2026-11-11 at 10 06 03" src="https://github.com/user-attachments/assets/8f4e91ed-aa02-4f35-b181-9bab29b931f4" />


**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| LCD RS | P2.0 | Register select (0 = command, 1 = data) |
| LCD RW | GND | Write-only |
| LCD E | P2.1 | Enable (latch on falling edge) |
| LCD D4–D7 | P2.4 – P2.7 | 4-bit data bus |
| LCD VSS / VDD / V0 | GND / +5 V / 10 kΩ pot | Power and contrast |
| LCD A / K | +5 V (via resistor) / GND | Backlight |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The LCD keeps characters in DDRAM. Row 1 starts at address 0x00 and row 2 at 0x40; the Set-DDRAM-Address command is 0x80 + address, so row 1 = 0x80 + col and row 2 = 0xC0 + col. Numbers must be converted to ASCII digits ('0' + digit) before being written.

**Pseudocode:**

1. `lcd_goto(row, col)`: send `0x80 + col` (row 0) or `0xC0 + col` (row 1).
2. `lcd_puts(str)`: send characters with `lcd_data()` until '\0'.
3. `lcd_print_number(val)`: extract digits by `% 10` and `/ 10`, then print in the correct order.
4. Print a fixed label (e.g. "Count:") once.
5. In a loop, move to the value position and print the updated number (pad with spaces to clear old digits).

**Code Base:**

Functions build on the Task 7A driver; `lcd_print_number()` uses a small digit buffer filled in reverse and printed from the most significant digit.

## 4. Inference

**Observation:**

Text appeared exactly at the requested row/column, and the counter value updated in place without clearing or flickering the rest of the screen.

**Conclusion:**

Knowing the DDRAM address map allows precise cursor positioning, and in-place updates are more efficient than clearing the whole display.
