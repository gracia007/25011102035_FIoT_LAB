# CAT8 – Task 8B – Event-Based Control

| Field | Details |
|---|---|
| **EXP** | CAT8 |
| **DATE** | 18/09/2026 |
| **NAME OF EXP** | STM32 GPIO Bring-Up and Switch-Controlled LED |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 Blue Pill (ARM Cortex-M3, 72 MHz), ST-Link V2, STM32CubeMX + Keil MDK-ARM (HAL), LED, push-button |
| **TASK NO** | Task 8B – Event-Based Control |

## 1. Objective

Modify the firmware so that each valid switch press toggles the LED state. Investigate switch bounce and implement a simple software solution to ensure one press produces one toggle.

## 2. Circuit Diagram

<img width="1600" height="1006" alt="WhatsApp Image 2026-11-11 at 10 06 03 (1)" src="https://github.com/user-attachments/assets/4742ee0c-690d-4c16-8cfd-cfec50f9e41a" />


**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| 3.3 V / GND | 3V3 / GND | Board supply from ST-Link / USB |
| HSE | 8 MHz crystal → PLL 72 MHz | System clock (configured in CubeMX) |
| LED | PC13 | Output (on-board LED, active-LOW) |
| Push-button | PA0 | Input, internal pull-up; other side to GND |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

Instead of the level, the firmware detects the press event (transition from released to pressed). A mechanical switch bounces for a few milliseconds, which looks like several presses; a time-based debounce using `HAL_GetTick()` accepts the press only if it is still stable after ~50 ms.

**Pseudocode:**

1. Store `prev = released`.
2. Read `curr` from the button.
3. If `prev == released` and `curr == pressed`, note `t = HAL_GetTick()`.
4. If still pressed after 50 ms, toggle the LED with `HAL_GPIO_TogglePin()`.
5. Wait for release, update `prev = curr`, repeat.

**Code Base:**

Edge detection with a `prev`/`curr` state pair and a 50 ms `HAL_GetTick()` window; `HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13)` toggles the LED.

## 4. Inference

**Observation:**

Without debouncing the LED sometimes toggled twice on one press. With the 50 ms debounce, every press toggled the LED exactly once.

**Conclusion:**

Switch bounce must be handled in software (or hardware); edge detection plus debouncing gives one clean event per press.
