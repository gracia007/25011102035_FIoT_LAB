# CAT2 – Task 3 – Customised Library Function for Delay

| Field | Details |
|---|---|
| **EXP** | CAT2 |
| **DATE** | 20/07/2026 |
| **NAME OF EXP** | 8051 Tool Chain Setup – Development Board – AT89S52 (GPIO Interfacing) |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, on-board user LED |
| **TASK NO** | Task 3 – Customised Library Function for Delay |

## 1. Objective

Develop a customised library function for delay functionality that can be reused across programs.

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| User LED | P1.0 | Used to verify the delay |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

With an 11.0592 MHz crystal, one machine cycle = 12 / 11.0592 MHz ≈ 1.085 µs. An inner loop is calibrated so that it takes about 1 ms; an outer loop repeats it `ms` times. Placing this in a separate `delay.c` / `delay.h` pair makes it a reusable library.

**Pseudocode:**

1. Create `delay.h` with the prototype `void delay_ms(unsigned int ms);`.
2. Create `delay.c` with an outer loop running `ms` times.
3. Inside it, run an inner loop (≈ 120 iterations) that takes about 1 ms.
4. Add `delay.c` to the Keil project and include `delay.h` in `main.c`.
5. Use `delay_ms(500)` in the LED blink program.
6. Verify the timing with a stopwatch or oscilloscope.

**Code Base:**

```c
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 120; j++);
}
```

## 4. Inference

**Observation:**

Calling `delay_ms(500)` produced a visible half-second delay, and the LED blink rate matched the expected ≈ 1 Hz.

**Conclusion:**

A custom delay library makes the code modular and reusable. Software delays are approximate (they depend on crystal frequency and compiler optimisation) and keep the CPU busy, which motivates hardware timers in later experiments.
