# CAT12 – Task 1 – On-board LED Bring-Up

| Field | Details |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 14/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4F, up to 84 MHz), on-board ST-Link, STM32CubeMX + Keil MDK-ARM (HAL), on-board LED LD2 and user button B1 |
| **TASK NO** | Task 1 – On-board LED Bring-Up |

## 1. Objective

Develop and program an STM32 application to verify the NUCLEO-F401RE hardware and GPIO output configuration by blinking the on-board LED at a fixed interval.

## 2. Circuit Diagram

<img width="1360" height="711" alt="03C3BCFF-EBD6-4B5C-A809-7C309858A5D0_1_201_a" src="https://github.com/user-attachments/assets/1e3946d9-ea31-47c0-a39b-5da9bc8000d0" />


**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| 3.3 V / GND | 3V3 / GND | Board supply from USB (ST-Link) |
| Clock | HSI 16 MHz / ST-Link MCO 8 MHz → PLL 84 MHz | System clock (configured in CubeMX) |
| LD2 (user LED) | PA5 | Output, active-HIGH |
| B1 (user button) | PC13 | Input, active-LOW (external pull-up on board) |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32F401RE (Cortex-M4F, up to 84 MHz, GPIO ports A–H, 3 USARTs, 3 I²C, 4 SPI) is configured in CubeMX with the PLL generating the system clock. PA5 (LD2) is configured as a push-pull output, and the LED is toggled at a fixed interval.

**Pseudocode:**

1. Initialise HAL and configure the system clock (PLL → 84 MHz).
2. Configure PA5 as GPIO_Output (`MX_GPIO_Init()`).
3. Toggle LD2 with `HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)`.
4. Wait 500 ms with `HAL_Delay()`.
5. Repeat continuously.

**Code Base:**

`HAL_GPIO_TogglePin()` and `HAL_Delay()` in `while(1)`.

**Board Specifications (Prerequisite):**

| Parameter | Value |
|---|---|
| MCU | STM32F401RET6 |
| Core | ARM Cortex-M4F |
| Max clock | 84 MHz |
| Flash / SRAM | 512 KB / 96 KB |
| GPIO ports | A, B, C, D, H |
| USART / I²C / SPI | 3 / 3 / 4 |
| On-board LED / button | LD2 = PA5, B1 = PC13 |


## 4. Inference

**Observation:**

LD2 blinked steadily at the programmed interval (1 s period).

**Conclusion:**

The NUCLEO-F401RE board, clock configuration and GPIO output are working correctly.
