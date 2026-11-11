# CAT7 – Task 7C – 4x4 Keypad-Based Character Movement

| Field | Details |
|---|---|
| **EXP** | CAT7 |
| **DATE** | 24/08/2026 |
| **NAME OF EXP** | 16x2 LCD Driver Development and Dynamic Display Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, 16x2 HD44780-compatible LCD (4-bit mode), 10 kΩ contrast potentiometer, 4x4 keypad |
| **TASK NO** | Task 7C – 4x4 Keypad-Based Character Movement |

## 1. Objective

Develop an interactive LCD application in which a character is moved across the 16x2 display using the 4x4 keypad. Keys 2, 8, 4 and 6 move the character Up, Down, Left and Right.

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

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
| Keypad rows R1–R4 | P1.0 – P1.3 | Outputs |
| Keypad columns C1–C4 | P1.4 – P1.7 | Inputs (pulled HIGH) |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The character's position is stored as (row, col). On each valid key press, the old position is overwritten with a space and the character is drawn at the new position using `lcd_goto()`. Boundary checks keep it inside rows 0–1 and columns 0–15.

**Pseudocode:**

1. Initialise LCD and keypad; set `row = 0`, `col = 0`; draw the character.
2. Scan the keypad (with debounce).
3. Key 2 ↑: `row = 0`; Key 8 ↓: `row = 1`.
4. Key 4 ←: `if (col > 0) col--`; Key 6 →: `if (col < 15) col++`.
5. Erase the old position (write ' ') and draw the character at the new position.
6. Repeat continuously.

**Code Base:**

Combines `keypad_scan()` from CAT4 with `lcd_goto()` and `lcd_data()` from Tasks 7A/7B.

| Key | Action |
|---|---|
| 2 | ↑ Move Up |
| 8 | ↓ Move Down |
| 4 | ← Move Left |
| 6 | → Move Right |


## 4. Inference

**Observation:**

The character moved one position per key press in the correct direction and stopped at the display edges.

**Conclusion:**

Integrating keypad input with LCD output creates an interactive interface, reusing the drivers developed in earlier tasks.
