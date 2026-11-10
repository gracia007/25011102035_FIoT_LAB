# CAT5 - Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

| Field | Details |
|---|---|
| **EXP** | CAT5 |
| **DATE** | 10/08/2026 |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision, LED, oscilloscope, stepper motor + driver |
| **TASK NO** | Task A - Timer 0 Periodic Interrupt (1 s LED toggle), Task B - LED Fading using Software PWM / Variable-Frequency Square-Wave Generation, Task C - Stepper-Motor Speed and Direction Control (optional) |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task A - Timer 0 Periodic Interrupt (1 s LED toggle)

**Project folder:** [`TASKA_Timer0_Interrupt_1s_LED_Toggle/`](TASKA_Timer0_Interrupt_1s_LED_Toggle/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

Timer 0 is used in 16-bit mode (Mode 1) to generate a periodic interrupt every 1 ms. With an 11.0592 MHz crystal one machine cycle is about 1.085 µs, so 922 counts give 1 ms and the reload value is 65536 − 922 = 64614 = 0xFC66. The ISR counts 1000 ticks to toggle an LED every second.

**Pseudocode:**

1. Set `TMOD = 0x01` (Timer 0, Mode 1).
2. Load `TH0 = 0xFC`, `TL0 = 0x66`.
3. Enable interrupts: `ET0 = 1`, `EA = 1`, then start the timer with `TR0 = 1`.
4. In the Timer 0 ISR, reload TH0/TL0 and increment a millisecond counter.
5. When the counter reaches 1000, toggle the LED and reset the counter.
6. The main loop stays free (non-blocking).

**Code Base:**

`void timer0_isr(void) interrupt 1` reloads the timer and maintains the software time base. No software delay loops are used; timing comes entirely from the hardware timer.

#### INFERENCE

The LED toggles every 1 second, which was verified on the oscilloscope. Hardware generates the timing and software only responds to the timing event, giving accurate, non-blocking timing.


### Task B - LED Fading using Software PWM / Variable-Frequency Square-Wave Generation

**Project folder:** [`TASKB_Software_PWM_LED_Fading_and_Square_Wave/`](TASKB_Software_PWM_LED_Fading_and_Square_Wave/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The 1 ms (or faster) timer tick is used as a time base for software PWM. A counter runs from 0 to the PWM period; the output is HIGH while the counter is below the duty value and LOW after it. Gradually changing the duty from 0% to 100% and back fades the LED. The same tick is used to toggle a GPIO pin at selected frequencies to generate square waves.

**Pseudocode:**

1. Configure Timer 0 for a fast periodic interrupt (e.g. 100 µs).
2. In the ISR, increment `pwm_count`; set the pin HIGH if `pwm_count < duty`, else LOW; wrap at the period (100 steps → 500 Hz–1 kHz).
3. Periodically step `duty` 0 → 100 → 0 % to produce fading.
4. For square-wave mode, toggle the output pin every N ticks, where N sets the frequency (100 Hz, 500 Hz, 1 kHz, 2 kHz, 5 kHz).
5. Generate other waveforms (variable duty, pulse train, burst) by changing the ON/OFF tick counts.
6. Measure frequency and duty cycle on the oscilloscope.

**Code Base:**

The timer ISR holds the PWM counter and compares it with the `duty` variable. The main loop only updates `duty` or the selected frequency mode, so the system stays non-blocking.

#### INFERENCE

The LED brightness changes smoothly from OFF to fully ON and back without visible flicker. Square waves of the selected frequencies were observed on the oscilloscope, showing that a single hardware timer interrupt can serve as a time base for PWM and pulse generation.


### Task C - Stepper-Motor Speed and Direction Control (optional)

**Project folder:** [`TASKC_Stepper_Motor_Speed_Direction/`](TASKC_Stepper_Motor_Speed_Direction/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The stepper motor is driven by outputting the step sequence 1000 → 0100 → 0010 → 0001 on four GPIO pins through a driver. Each timer interrupt (or group of ticks) advances one step, so the timer interval sets the speed and the sequence direction sets the rotation direction.

**Pseudocode:**

1. Configure Timer 0 for a 1 ms tick.
2. Store the step sequence in an array `{0x08, 0x04, 0x02, 0x01}`.
3. In the ISR, count ticks until the step interval is reached (100 ms slow, 50 ms medium, 10 ms fast).
4. Output the next pattern to the motor port.
5. Increment the index for clockwise or decrement it for anticlockwise rotation.
6. Repeat continuously.

**Code Base:**

A step index and a step-interval variable are updated inside the timer ISR; changing the interval changes the speed and changing the index direction reverses the motor.

#### INFERENCE

The stepper motor rotates at the selected speed and direction. Shorter timer intervals produce faster rotation, showing that the timer interval directly controls motor speed. (Optional task.)
