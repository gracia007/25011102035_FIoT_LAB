# CAT9 - STM32 UART Command Controlled LED

| Field | Details |
|---|---|
| **EXP** | CAT9 |
| **DATE** | 28/09/2026 |
| **NAME OF EXP** | STM32 UART Command Controlled LED |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill, ARM Cortex-M3), ST-Link debugger, STM32CubeMX + Keil MDK, USB-to-TTL converter, PC terminal (PuTTY) |
| **TASK NO** | Task 9A - Basic UART Communication, Task 9B - String-Based Application Logic |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task 9A - Basic UART Communication

**Project folder:** [`TASKA_Basic_UART_Communication/`](TASKA_Basic_UART_Communication/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

A USART is configured in STM32CubeMX for 9600 (or 115200) baud, 8 data bits, no parity, 1 stop bit and connected to a PC terminal through a USB-to-TTL converter. Characters and strings are transmitted with `HAL_UART_Transmit()`, and every received character is echoed back.

**Pseudocode:**

1. Initialise the HAL and the USART (`MX_USARTx_UART_Init()`).
2. Transmit a character repeatedly to the PC terminal.
3. Receive one character with `HAL_UART_Receive()`.
4. Transmit the same character back to the PC.
5. Test the strings "HELLO\r\n", "HELLO\r", "HELLO\n" and "HELLO\r\nWORLD\r\n" and observe the PuTTY output.
6. Repeat continuously.

**Code Base:**

`HAL_UART_Init()`, `HAL_UART_Transmit()` and `HAL_UART_Receive()` are used for basic polling-mode serial communication.

#### INFERENCE

Characters typed in PuTTY are echoed back by the STM32. `\r` returns the cursor to the start of the line and `\n` moves to the next line, so both CR and LF are needed for a proper new line on the terminal.


### Task 9B - String-Based Application Logic

**Project folder:** [`TASKB_String_Based_Application_Logic/`](TASKB_String_Based_Application_Logic/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

A UART command interface is built. Received characters are collected into a buffer until Enter (`\r` or `\n`) is received. The completed string is then compared with known commands to control the onboard LED, and a response is sent back.

**Pseudocode:**

1. Initialise the HAL, UART and LED GPIO.
2. Receive characters one at a time and store them in `cmd[]`.
3. On `\r` or `\n`, terminate the string with '\0'.
4. If `cmd == "LED ON"`, turn the LED ON and reply "LED turned ON".
5. If `cmd == "LED OFF"`, turn the LED OFF and reply "LED turned OFF".
6. If `cmd == "LED TOGGLE"`, toggle the LED and reply "LED toggled".
7. Otherwise reply "Unknown command"; clear the buffer and repeat.

**Code Base:**

`strcmp()` is used for command matching, `HAL_GPIO_WritePin()` / `HAL_GPIO_TogglePin()` control the LED, and `HAL_UART_Transmit()` sends the replies.

#### INFERENCE

The LED responds correctly to LED ON, LED OFF and LED TOGGLE commands typed in the terminal, with a confirmation message for each. This shows string-based command parsing over UART for device control.
