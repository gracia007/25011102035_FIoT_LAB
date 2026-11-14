# CAT3 – Timer-Based LED Pattern Generator and Button Interrupt Controller

| Field | Details |
|---|---|
| **EXP** | CAT3 |
| **DATE** | 27/07/2026 |
| **NAME OF EXP** | Timer-Based LED Pattern Generator and Button Interrupt Controller |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, 4 LEDs, 1 push-button |
| **TASK NO** | Single task – Four-State LED Control System |

## 1. Objective

Design and implement a register-level GPIO controller. Configure four LEDs as digital outputs and a push-button as a digital input. Using only bare-metal Embedded C and direct register access, develop a four-state LED control system in which each valid button press advances to the next mode: running LED, binary counter, alternating pattern and all-LED flashing. Implement switch debouncing so that one physical press produces exactly one state transition.

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| LED1–LED4 | P1.0 – P1.3 | Outputs, active-LOW |
| Push-button | P3.2 (INT0) | Input, to GND when pressed (internal pull-up) |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The system is a finite-state machine with four modes. The button is read from a port pin; when a press is detected, the program waits about 20 ms and checks again to reject switch bounce, then waits for release so that one press causes one transition. The current mode decides which LED pattern is written to the lower nibble of Port 1.

**Pseudocode:**

1. Initialise P1 with all LEDs OFF and set the button pin as input (write 1).
2. Set `mode = 0`.
3. Check the button; if pressed, wait 20 ms (debounce) and re-check.
4. If still pressed, set `mode = (mode % 4) + 1` and wait for release.
5. Mode 1 – Running LED: LED1 → LED2 → LED3 → LED4 → LED1 …
6. Mode 2 – Binary counter: 0000 → 0001 → … → 1111 → 0000.
7. Mode 3 – Alternating pattern: 1010 ↔ 0101.
8. Mode 4 – All-LED flash: 1111 ↔ 0000.
9. Repeat the loop continuously.

**Code Base:**

A `switch(mode)` selects one of four pattern functions. Each pattern step is written to the port as a 4-bit value, for example `P1 = (P1 & 0xF0) | (~pattern & 0x0F);` for active-LOW LEDs. Button handling uses press detection, a 20 ms debounce delay and a wait-for-release loop.

**Required Behaviour:**

| Mode | LED Output |
|---|---|
| Mode 1 – Running LED | LED1 → LED2 → LED3 → LED4 → LED1 … |
| Mode 2 – Binary Counter | 0000, 0001, 0010, … 1111, 0000 |
| Mode 3 – Alternating Pattern | 1010, 0101, 1010, 0101 |
| Mode 4 – All LED Flash | 1111, 0000, 1111, 0000 |


## 4. Inference

**Observation:**

Initially all LEDs were OFF. Each button press moved the system to the next mode in order (running LED → binary counter → alternating → all flash → running LED). With debouncing, one press always caused exactly one mode change.

**Conclusion:**

Register-level GPIO input/output can implement a reliable state machine. Switch debouncing is essential because a mechanical switch bounces and would otherwise trigger several transitions per press.
