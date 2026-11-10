# CAT2 - 8051 Tool Chain setup - Development Board - AT89S52 (GPIO: Bare-Metal LED Blink)

| Field | Details |
|---|---|
| **EXP** | CAT2 |
| **DATE** | 20/07/2026 |
| **NAME OF EXP** | 8051 Tool Chain setup - Development Board - AT89S52 (GPIO: Bare-Metal LED Blink) |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision, on-board LED |
| **TASK NO** | Task A - Hardware Board Bring-Up, Task B - Bare-Metal LED Blink, Task C - Customised Library Function for Delay |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task A - Hardware Board Bring-Up

**Project folder:** [`TASKA_Hardware_Board_Bring_Up/`](TASKA_Hardware_Board_Bring_Up/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The AT89S52 development board is brought up by identifying the microcontroller, the programmer/debug interface, the power source and the user LED. The board's power rails are checked with a digital multimeter, and the LED's GPIO port and pin are found from the board schematic.

**Pseudocode:**

1. Identify the MCU (AT89S52, 8051 core), the programmer interface and the power source.
2. Measure VCC and GND on the board with a multimeter to verify the power rails.
3. Locate the user LED and its port/pin on the board schematic.
4. Note whether the LED is active-HIGH or active-LOW.
5. Establish communication between the host PC and the target MCU and flash a test program.
6. Fill in the Hardware Bring-Up Sheet (MCU, CPU core, operating voltage, debug interface, LED port, LED pin, active state, frequency).

**Code Base:**

No application logic; this task records the hardware parameters in the bring-up sheet and confirms that the toolchain (Keil uVision) can build and flash a program to the board.

#### INFERENCE

The board was powered and verified, the LED GPIO port/pin and its active state were identified from the schematic, and the host PC successfully programmed the AT89S52, confirming a working toolchain and hardware setup.


### Task B - Bare-Metal LED Blink

**Project folder:** [`TASKB_Bare_Metal_LED_Blink/`](TASKB_Bare_Metal_LED_Blink/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment demonstrates bare-metal GPIO output control on the 8051. The LED pin is driven by writing directly to the memory-mapped port SFR, without any Arduino APIs, HAL libraries or RTOS services.

**Pseudocode:**

1. Include the `reg51.h` SFR definitions.
2. Define the LED pin using `sbit` on the LED port.
3. Turn the LED ON by writing the active level to the pin.
4. Introduce a software delay of about 500 ms.
5. Turn the LED OFF.
6. Introduce a software delay of about 500 ms.
7. Repeat the process continuously.

**Code Base:**

The LED is controlled by writing directly to the port bit (`LED = 0;` / `LED = 1;`), and a nested `for` loop is used as a software delay to produce a blink rate of about 1 Hz.

#### INFERENCE

The on-board LED blinks at approximately 1 Hz, demonstrating that the 8051 GPIO can be controlled by direct register (SFR) access and that a calibrated software loop can generate a timing delay.


### Task C - Customised Library Function for Delay

**Project folder:** [`TASKC_Custom_Delay_Library/`](TASKC_Custom_Delay_Library/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

A reusable delay function is written as a custom library. The delay in milliseconds is produced by a loop count calibrated to the 11.0592 MHz crystal (1 machine cycle ≈ 1.085 µs), so that application code can call a single function instead of repeating loops.

**Pseudocode:**

1. Create `delay.h` with the prototype `void delay_ms(unsigned int ms);`.
2. Create `delay.c` implementing an outer loop that runs `ms` times.
3. Inside it, run an inner loop calibrated to take about 1 ms.
4. Include `delay.h` in `main.c`.
5. Call `delay_ms()` from the LED blink loop.
6. Verify the blink period with a stopwatch or oscilloscope.

**Code Base:**

`delay_ms(unsigned int ms)` uses two nested `for` loops; the inner count (≈ 120 iterations for 11.0592 MHz) is tuned so that one outer iteration takes about 1 ms.

#### INFERENCE

The custom delay library produces consistent millisecond delays and makes the code modular and reusable. Software delays depend on the crystal frequency and compiler optimisation, so they are approximate and block the CPU while running.
