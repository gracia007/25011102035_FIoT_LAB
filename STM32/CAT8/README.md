# CAT8 - STM32 GPIO Bring-Up and Switch-Controlled LED

| Field | Details |
|---|---|
| **EXP** | CAT8 |
| **DATE** | 18/09/2026 |
| **NAME OF EXP** | STM32 GPIO Bring-Up and Switch-Controlled LED |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill, ARM Cortex-M3), ST-Link debugger, STM32CubeMX + Keil MDK, LED, push-button |
| **TASK NO** | Task 8A - GPIO Input/Output, Task 8B - Event-Based Control, Task 8C - Short Press vs Long Press |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task 8A - GPIO Input/Output

**Project folder:** [`TASKA_GPIO_Input_Output/`](TASKA_GPIO_Input_Output/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment demonstrates GPIO input and output using the STM32 HAL library. The push-button pin is configured as a digital input with pull-up, and PC13 is configured as a digital output to control the LED. The LED state follows the switch state.

**Pseudocode:**

1. Initialise the HAL library and system clock.
2. Configure the LED pin (PC13) as output and the button pin as input with pull-up.
3. Read the button with `HAL_GPIO_ReadPin()`.
4. If pressed, turn the LED ON; otherwise turn it OFF.
5. Repeat the process continuously.

**Code Base:**

GPIO is configured in STM32CubeMX and the logic uses `HAL_GPIO_ReadPin()` and `HAL_GPIO_WritePin()` inside the `while(1)` loop.

#### INFERENCE

The LED turns ON while the button is pressed and OFF when it is released, demonstrating GPIO input reading and output control using STM32 HAL functions.


### Task 8B - Event-Based Control

**Project folder:** [`TASKB_Event_Based_Control/`](TASKB_Event_Based_Control/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

Each valid button press toggles the LED. The firmware detects the press edge (released → pressed) instead of the level, and uses a short time-based debounce so that switch bounce does not cause multiple toggles.

**Pseudocode:**

1. Initialise the HAL, LED output and button input.
2. Read the current button state.
3. If a falling edge is detected (previous = released, current = pressed), record `HAL_GetTick()`.
4. If the button is still pressed after about 50 ms, toggle the LED.
5. Wait for the button to be released.
6. Store the current state as the previous state and repeat.

**Code Base:**

`HAL_GPIO_TogglePin()` toggles the LED, and `HAL_GetTick()` is used for the debounce interval.

#### INFERENCE

Each button press toggles the LED exactly once. Switch bounce, which otherwise causes multiple toggles, is removed by the software debounce.


### Task 8C - Short Press vs Long Press

**Project folder:** [`TASKC_Short_vs_Long_Press/`](TASKC_Short_vs_Long_Press/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The duration of each press is measured using the HAL millisecond tick. A press shorter than 1 s is a short press; 1 s or longer is a long press. A short press toggles the LED (or stops blinking); a long press puts the LED into continuous blinking mode.

**Pseudocode:**

1. On press, record `start = HAL_GetTick()`.
2. On release, compute `duration = HAL_GetTick() − start`.
3. If duration < 1000 ms (short press): if blinking, stop blinking; otherwise toggle the LED.
4. If duration ≥ 1000 ms (long press): enter blinking mode.
5. In blinking mode, toggle the LED every 250 ms using `HAL_GetTick()` (non-blocking).
6. Repeat continuously.

**Code Base:**

Press timing and blinking both use `HAL_GetTick()`, so `HAL_Delay()` is not needed and the button stays responsive while the LED is blinking.

#### INFERENCE

Short and long presses are correctly classified: a short press toggles the LED or stops blinking, and a long press starts continuous blinking. Using `HAL_GetTick()` keeps the system non-blocking.
