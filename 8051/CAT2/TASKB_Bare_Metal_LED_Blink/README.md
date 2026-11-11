# CAT2 – Task 2 – Bare-Metal LED Blink

| Field | Details |
|---|---|
| **EXP** | CAT2 |
| **DATE** | 20/07/2026 |
| **NAME OF EXP** | 8051 Tool Chain Setup – Development Board – AT89S52 (GPIO Interfacing) |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, on-board user LED |
| **TASK NO** | Task 2 – Bare-Metal LED Blink |

## 1. Objective

Configure the LED GPIO as an output using direct register access, write a delay mechanism using a simple software loop, and blink the LED at approximately 1 Hz.

## 2. Circuit Diagram

<img width="1645" height="956" alt="image" src="https://github.com/user-attachments/assets/d0c0fb56-dc1e-44da-99e1-82811dd364cf" />


**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| User LED | P1.0 | Output, active-LOW |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The 8051 ports are memory-mapped Special Function Registers (SFRs). Writing to a port bit directly drives the corresponding pin, so the LED is controlled by writing 0 or 1 to `P1^0`. A software loop that burns a known number of machine cycles provides the delay.

**Pseudocode:**

1. Include `reg51.h` for the SFR definitions.
2. Declare the LED pin: `sbit LED = P1^0;`.
3. Turn the LED ON (`LED = 0`).
4. Call a software delay of about 500 ms.
5. Turn the LED OFF (`LED = 1`).
6. Call a software delay of about 500 ms.
7. Repeat forever in `while(1)`.

**Code Base:**

```c
sbit LED = P1^0;
void main(void) {
    while (1) {
        LED = 0;  delay_ms(500);   // ON
        LED = 1;  delay_ms(500);   // OFF
    }
}
```
The delay is a nested `for` loop; no timers, interrupts or libraries are used.

## 4. Inference

**Observation:**

The LED blinks continuously with a period of about 1 second (≈ 1 Hz).

**Conclusion:**

GPIO can be controlled at bare-metal level by writing directly to port SFRs, and a calibrated software loop is enough to generate a simple timing delay.
