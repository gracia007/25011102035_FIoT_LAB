# CAT4 – Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display

| Field | Details |
|---|---|
| **EXP** | CAT4 |
| **DATE** | 03/08/2026 |
| **NAME OF EXP** | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, 4x4 matrix keypad, common-anode seven-segment display, 4 LEDs |
| **TASK NO** | Single task – Keypad-Controlled HMI |

## 1. Objective

Design a simple embedded user interface in which the keypad acts as the input device, the seven-segment display provides visual feedback and the LEDs indicate different operating modes. Whenever a valid key is pressed, display the key value on the seven-segment display and execute the corresponding LED function.

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| Keypad rows R1–R4 | P2.0 – P2.3 | Outputs (driven LOW one at a time) |
| Keypad columns C1–C4 | P2.4 – P2.7 | Inputs (pulled HIGH) |
| Seven-segment a–g, dp | P0.0 – P0.7 | Segment lines (external pull-ups on P0) |
| LED1–LED4 | P1.0 – P1.3 | Outputs, active-LOW |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The 4x4 keypad is scanned row by row: one row is driven LOW and the columns are read. A LOW column identifies the pressed key at that row/column intersection. The key value is converted to a segment pattern using a lookup table and written to Port 0, and `led_control()` runs the LED function mapped to that key.

**Pseudocode:**

1. Initialise ports: all LEDs OFF, display blank, keypad rows HIGH.
2. `keypad_scan()`: for each row, drive it LOW and read the columns.
3. If a column is LOW, decode the key, debounce and wait for release.
4. `display_digit(key)`: write `seg_code[key]` to the display port.
5. `led_control(key)`: execute the LED function for that key (see table).
6. Repeat continuously.

**Code Base:**

The program is split into the required functions: `keypad_scan()`, `display_digit(unsigned char value)`, `led_control(unsigned char key)`, `running_led()`, `binary_counter()`, `alternate_led()` and `blink_all()`. A `seg_code[10]` array holds the seven-segment patterns for digits 0–9.

**Functional Requirements:**

| Key Press | Seven-Segment Display | LED Operation |
|---|---|---|
| 1 | 1 | LED1 ON |
| 2 | 2 | LED2 ON |
| 3 | 3 | LED3 ON |
| 4 | 4 | LED4 ON |
| 5 | 5 | Running LED pattern |
| 6 | 6 | Alternate LEDs (1010 ↔ 0101) |
| 7 | 7 | Binary counter (0–15) |
| 8 | 8 | All LEDs blink |
| 9 | 9 | All LEDs OFF |
| 0 | 0 | Reset system |


## 4. Inference

**Observation:**

Every valid key press was shown on the seven-segment display and the matching LED operation was executed as per the table. Key 0 reset the system to its initial state.

**Conclusion:**

Row/column scanning reads 16 keys with only 8 I/O lines, and a lookup table makes seven-segment driving simple. Splitting the program into separate functions gives a clean, modular HMI design.
