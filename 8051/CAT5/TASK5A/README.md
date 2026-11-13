# CAT5 – Task 1 – Timer 0 Periodic Interrupt (1 s LED Toggle)

| Field | Details |
|---|---|
| **EXP** | CAT5 |
| **DATE** | 10/08/2026 |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, LED, oscilloscope, stepper motor with ULN2003 driver |
| **TASK NO** | Task 1 – Timer 0 Periodic Interrupt (1 s LED Toggle) |

## 1. Objective

Configure Timer 0 to generate a precise periodic interrupt. Use the timer interrupt to create a software time base and toggle an LED every 1 second. Verify the generated timing using an oscilloscope.

## 2. Circuit Diagram

<img width="1600" height="1177" alt="WhatsApp Image 2026-11-11 at 10 06 03" src="https://github.com/user-attachments/assets/b0bb1265-939b-4948-9b9c-9882bfe36abe" />

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| LED | P1.0 | Output toggled every 1 s (also probed on oscilloscope) |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

Timer 0 in Mode 1 (16-bit). For a 1 ms tick at 11.0592 MHz: machine cycle ≈ 1.085 µs, N = 1 ms / 1.085 µs ≈ 922, reload = 65536 − 922 = 64614 = **0xFC66** → `TH0 = 0xFC; TL0 = 0x66;`. Crystal → machine cycle → timer counter → overflow → interrupt → software time base → 1-second LED control. The ISR counts 1000 ticks of 1 ms to obtain 1 second.

**Pseudocode:**

1. `TMOD = 0x01` (Timer 0, Mode 1).
2. Load `TH0 = 0xFC`, `TL0 = 0x66`.
3. Enable interrupts: `ET0 = 1; EA = 1;` and start: `TR0 = 1;`.
4. In the Timer 0 ISR: reload TH0/TL0 and increment `ms_count`.
5. When `ms_count == 1000`: toggle the LED and clear `ms_count`.
6. The main loop remains free for other work (non-blocking).

**Code Base:**

```c
void timer0_isr(void) interrupt 1 {
    TH0 = 0xFC; TL0 = 0x66;      // reload for 1 ms
    if (++ms_count >= 1000) {
        ms_count = 0;
        LED = ~LED;              // toggle every 1 s
    }
}
```

## 4. Inference

**Observation:**

The LED toggled every second; on the oscilloscope the pin showed a square wave with a 2 s period (1 s HIGH, 1 s LOW).

**Conclusion:**

Hardware generates the timing and software only responds to the timing event, so the timing is accurate and does not block the CPU.
