# CAT12 – Task 2 – On-board Switch Control with State Remembrance

| Field | Details |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 14/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4F, up to 84 MHz), on-board ST-Link, STM32CubeMX + Keil MDK-ARM (HAL), on-board LED LD2 and user button B1 |
| **TASK NO** | Task 2 – On-board Switch Control with State Remembrance |

## 1. Objective

Modify the application so that the on-board push button controls the LED. The LED shall toggle its state whenever a valid button press is detected and shall remember its previous state after the button is released.

## 2. Circuit Diagram

 <img width="1360" height="711" alt="03C3BCFF-EBD6-4B5C-A809-7C309858A5D0_1_201_a" src="https://github.com/user-attachments/assets/0a92bbb5-8fb1-4f23-9ec6-e1f8668d22c7" />



**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| 3.3 V / GND | 3V3 / GND | Board supply from USB (ST-Link) |
| Clock | HSI 16 MHz / ST-Link MCO 8 MHz → PLL 84 MHz | System clock (configured in CubeMX) |
| LD2 (user LED) | PA5 | Output, active-HIGH |
| B1 (user button) | PC13 | Input, active-LOW (external pull-up on board) |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

B1 on PC13 is active-LOW. The firmware stores the LED state in a variable and only changes it on a valid press edge (HIGH → LOW), confirmed by a ~50 ms debounce. Because the state is stored, the LED keeps its value after release.

**Pseudocode:**

1. Configure PC13 as input and PA5 as output.
2. Detect the HIGH → LOW edge on PC13.
3. Debounce for 50 ms (`HAL_GetTick()`) and confirm the press.
4. `led_state = !led_state` and write it to PA5.
5. Wait for release; the LED keeps `led_state`.
6. Repeat continuously.

**Code Base:**

`led_state` variable with `HAL_GPIO_ReadPin()`, `HAL_GPIO_WritePin()` and `HAL_GetTick()`-based debounce.

## 4. Inference

**Observation:**

Each press of B1 toggled LD2, and the LED stayed in its new state after the button was released.

**Conclusion:**

Edge-triggered, debounced input with a stored state variable gives reliable toggle behaviour with state retention.
