# CAT5 – Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control

| Field | Details |
|---|---|
| **EXP** | CAT5 |
| **DATE** | 10/08/2026 |
| **NAME OF EXP** | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, LED, oscilloscope, stepper motor with ULN2003 driver |
| **TASK NO** | Task 1 – Timer 0 Periodic Interrupt (1 s LED Toggle), Task 2 – LED Fading using Software PWM and Variable-Frequency Square-Wave Generation, Task 3 – Stepper-Motor Speed and Direction Control (Optional) |

## Overview

Design a timer-driven embedded control system on the 8051 in which a hardware timer periodically generates interrupts. The timer interrupt is the system time base used to control LED brightness, generate a variable-frequency pulse signal and control the stepping sequence of a stepper motor. The implementation is non-blocking and does not use software delay loops for timing.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task 1 – Timer 0 Periodic Interrupt (1 s LED Toggle) | [`TASKA_Timer0_Interrupt_1s_LED_Toggle/`](TASKA_Timer0_Interrupt_1s_LED_Toggle/) | Timer 0 1 ms interrupt as software time base, LED toggles every 1 s |
| Task 2 – LED Fading using Software PWM and Variable-Frequency Square-Wave Generation | [`TASKB_Software_PWM_LED_Fading_and_Square_Wave/`](TASKB_Software_PWM_LED_Fading_and_Square_Wave/) | Software PWM fade 0→100→0 %, square waves 100 Hz–5 kHz and other waveforms |
| Task 3 – Stepper-Motor Speed and Direction Control (Optional) | [`TASKC_Stepper_Motor_Speed_Direction/`](TASKC_Stepper_Motor_Speed_Direction/) | Timer-driven step sequence; interval sets speed, sequence order sets direction |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
