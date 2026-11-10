# CAT12 - STM32F401RE Cortex-M4: GPIO and User Input Programming

| Field | Details |
|---|---|
| **EXP** | CAT12 |
| **DATE** | 14/10/2026 |
| **NAME OF EXP** | STM32F401RE Cortex-M4: GPIO and User Input Programming |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4), on-board ST-Link, STM32CubeMX + Keil MDK, on-board LED (LD2) and user button (B1) |
| **TASK NO** | Task 1 - On-board LED Bring-Up, Task 2 - On-board Switch Control with State Remembrance, Task 3 - Short-Press and Long-Press Detection |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task 1 - On-board LED Bring-Up

**Project folder:** [`TASKA_Onboard_LED_Bring_Up/`](TASKA_Onboard_LED_Bring_Up/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment demonstrates GPIO output on the NUCLEO-F401RE (Cortex-M4) using the STM32 HAL library. The on-board LED LD2 on PA5 is configured as a digital output. The clock is configured in CubeMX after checking the on-board oscillator.

**Pseudocode:**

1. Initialise the HAL library and configure the system clock.
2. Configure PA5 (LD2) as output.
3. Toggle the LED.
4. Introduce a fixed delay (e.g. 500 ms).
5. Repeat continuously.

**Code Base:**

`HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)` and `HAL_Delay()` are used inside the `while(1)` loop.

#### INFERENCE

The on-board LED of the NUCLEO-F401RE blinks at a fixed interval, verifying the board hardware, clock configuration and GPIO output configuration.


### Task 2 - On-board Switch Control with State Remembrance

**Project folder:** [`TASKB_Switch_Control_State_Remembrance/`](TASKB_Switch_Control_State_Remembrance/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The on-board user button B1 (PC13, active-LOW) controls the LED. A valid press is detected on the edge with debounce, and the LED toggles and keeps its new state after the button is released (state remembrance).

**Pseudocode:**

1. Configure PC13 as input and PA5 as output.
2. Read the button; detect the transition from released (HIGH) to pressed (LOW).
3. Debounce for about 50 ms and confirm the press.
4. Toggle the LED state variable and write it to PA5.
5. Wait for button release; the LED keeps its state.
6. Repeat continuously.

**Code Base:**

A `led_state` variable stores the current LED state. `HAL_GPIO_ReadPin()`, `HAL_GPIO_WritePin()` and `HAL_GetTick()` implement edge detection and debounce.

#### INFERENCE

Each press of the user button toggles the LED, and the LED keeps its state after release, showing edge-based input handling and state retention.


### Task 3 - Short-Press and Long-Press Detection

**Project folder:** [`TASKC_Short_and_Long_Press_Detection/`](TASKC_Short_and_Long_Press_Detection/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

Press duration is measured with `HAL_GetTick()`. A press shorter than 1 s is a short press and toggles the LED; a press of 1 s or more is a long press and switches the LED into (or out of) blinking mode.

**Pseudocode:**

1. On press, store `start = HAL_GetTick()`.
2. On release, compute the duration.
3. If duration < 1000 ms, perform the short-press action (toggle LED / stop blinking).
4. If duration ≥ 1000 ms, perform the long-press action (start blinking).
5. In blinking mode, toggle the LED using a non-blocking time check.
6. Repeat continuously.

**Code Base:**

Uses `HAL_GetTick()` for both press timing and blinking so that button input is never blocked.

#### INFERENCE

Short and long presses trigger different actions as expected, showing that press duration can be measured reliably with the HAL millisecond tick.
