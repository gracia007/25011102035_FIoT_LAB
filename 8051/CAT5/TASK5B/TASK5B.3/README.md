# CAT5 – Task 2 – LED Fading using Software PWM and Variable-Frequency Square-Wave Generation

| Field | Details |
|---|---|
| **EXP** | CAT5 |
| **DATE** | 10/08/2026 |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, LED, oscilloscope, stepper motor with ULN2003 driver |
| **TASK NO** | Task 2 – LED Fading using Software PWM and Variable-Frequency Square-Wave Generation |

## 1. Objective

Using the timer interrupt from Task 1, generate a software PWM signal and gradually vary the duty cycle from 0 % to 100 % and back to 0 % to produce a visible LED fading effect (PWM frequency ≈ 500 Hz – 1 kHz). Also configure a GPIO pin as a signal output and use the timer interrupt to generate square waves of 100 Hz, 500 Hz, 1 kHz, 2 kHz and 5 kHz, plus a variable duty-cycle wave, a pulse train and a burst signal. Measure frequency and duty cycle using an oscilloscope.

## 2. Circuit Diagram

<img width="1600" height="1177" alt="WhatsApp Image 2026-11-11 at 10 06 03 (1)" src="https://github.com/user-attachments/assets/5fa78b4f-7d8a-4fd0-9e52-6e0b17ce7ac1" />

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| LED (PWM output) | P1.0 | Software PWM for fading |
| Signal output | P1.1 | Square wave / waveform output to oscilloscope |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

A fast timer tick (e.g. 10 µs in Mode 2 auto-reload) drives a PWM counter. The output is HIGH while `pwm_count < duty` and LOW otherwise; with 100 steps per period the PWM frequency is ≈ 1 kHz, so the LED looks continuously lit and its brightness follows the duty cycle. For square waves, the output pin is toggled every N ticks, where N = f_tick / (2 × f_out).

**Pseudocode:**

1. Configure the timer for a fast periodic interrupt and enable it.
2. ISR: increment `pwm_count` (0–99); set LED pin HIGH if `pwm_count < duty`, else LOW.
3. Every ~20 ms, step `duty` by 10 % from 0 % up to 100 % and back down to 0 %.
4. Square-wave mode: count ticks and toggle the signal pin every N ticks for the selected mode (100 Hz, 500 Hz, 1 kHz, 2 kHz, 5 kHz).
5. Other waveforms: change the ON/OFF tick pattern (e.g. 1111000011110000, 1000000001000000…, bursts).
6. Measure each output on the oscilloscope.

**Code Base:**

The ISR holds the PWM counter and compares it with the global `duty`; the main loop only changes `duty` or the selected frequency `mode`, so the system stays non-blocking.

**Duty Cycle vs Brightness:**

| Duty Cycle | LED Brightness |
|---|---|
| 0 % | OFF |
| 25 % | Dim |
| 50 % | Medium |
| 75 % | Bright |
| 100 % | Fully ON |


## 4. Inference

**Observation:**

The LED faded smoothly from OFF to fully ON and back without visible flicker. The oscilloscope showed square waves at the selected frequencies and the expected duty cycles for each waveform type.

**Conclusion:**

One hardware timer interrupt can serve as a common time base for PWM brightness control and for generating several frequencies and waveforms, all without blocking delays.
