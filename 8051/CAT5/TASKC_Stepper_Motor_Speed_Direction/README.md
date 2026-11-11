# CAT5 – Task 3 – Stepper-Motor Speed and Direction Control (Optional)

| Field | Details |
|---|---|
| **EXP** | CAT5 |
| **DATE** | 10/08/2026 |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, LED, oscilloscope, stepper motor with ULN2003 driver |
| **TASK NO** | Task 3 – Stepper-Motor Speed and Direction Control (Optional) |

## 1. Objective

Use the timer interrupt to generate the stepping sequence of a stepper motor and control its speed and direction. The timer interval determines the motor speed (slow 100 ms/step, medium 50 ms/step, fast 10 ms/step).

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| Coils A, B, C, D (via ULN2003) | P2.0 – P2.3 | Step sequence outputs |
| Motor supply | +5 V / +12 V (external) | Stepper motor power through driver |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

A unipolar stepper motor rotates one step each time the next coil is energised. The sequence 1000 → 0100 → 0010 → 0001 is output on four pins through a ULN2003 driver. Each timer tick counts towards the step interval; when it expires, the next pattern is output. A shorter interval gives a higher speed, and reversing the sequence reverses the direction.

**Pseudocode:**

1. Configure Timer 0 for a 1 ms tick.
2. Store the sequence `{0x08, 0x04, 0x02, 0x01}`.
3. Set `step_interval` = 100, 50 or 10 ms for slow, medium or fast.
4. In the ISR, when the tick count reaches `step_interval`, output the next pattern.
5. Increment the index for clockwise, decrement it for anticlockwise.
6. Repeat continuously.

**Code Base:**

The ISR updates `step_index` and writes `step_seq[step_index]` to the motor port; `step_interval` and `direction` are global variables changed from the main loop.

## 4. Inference

**Observation:**

The motor rotated at three clearly different speeds for 100, 50 and 10 ms/step and reversed direction when the sequence order was reversed.

**Conclusion:**

The timer interval directly controls stepper speed, and the order of the step sequence controls direction, showing precise, interrupt-driven motor control.
