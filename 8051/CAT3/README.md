# CAT3 - Timer-Based LED Pattern Generator and Button Interrupt Controller

| Field | Details |
|---|---|
| **EXP** | CAT3 |
| **DATE** | 27/07/2026 |
| **NAME OF EXP** | Timer-Based LED Pattern Generator and Button Interrupt Controller |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision, 4 LEDs, 1 push-button |
| **TASK NO** | Single task (no subdivisions in the questions PDF) |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Core Logic / Pseudocode / Code Base

**Working Principle:**

Four LEDs are configured as outputs and a push-button as an input, all through direct SFR access. The system is a four-state machine: each valid (debounced) button press advances to the next mode — running LED, binary counter, alternating pattern and all-LED flash.

**Pseudocode:**

1. Initialise the LED port with all LEDs OFF and the button pin as input (write 1).
2. Set `mode = 0` (idle).
3. In the main loop, check the button for a press.
4. On press, wait about 20 ms (debounce) and confirm it is still pressed.
5. Advance `mode = (mode % 4) + 1` and wait for the button to be released.
6. Run one step of the pattern for the current mode: Mode 1 running LED, Mode 2 binary counter 0000–1111, Mode 3 alternating 1010/0101, Mode 4 all-LED flash 1111/0000.
7. Repeat the process continuously.

**Code Base:**

A `switch(mode)` statement selects the pattern function. Button handling uses press detection, a debounce delay and a wait-for-release loop so that one physical press causes exactly one state transition. LED patterns are written to the port as nibble values.

## INFERENCE

Each button press moves the system to the next operating mode, and debouncing ensures that one physical press produces exactly one state transition. This demonstrates register-level GPIO input/output and a simple finite-state-machine design.
