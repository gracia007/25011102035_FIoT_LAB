# CAT6 - UART Driver and Serial Debugging

| Field | Details |
|---|---|
| **EXP** | CAT6 |
| **DATE** | 17/08/2026 |
| **NAME OF EXP** | UART Driver and Serial Debugging |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision, USB-to-TTL converter, PC terminal (PuTTY) |
| **TASK NO** | Task A - UART Initialization and Character Transmission, Task B - UART Echo |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task A - UART Initialization and Character Transmission

**Project folder:** [`TASKA_UART_Init_and_Char_Transmission/`](TASKA_UART_Init_and_Char_Transmission/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The 8051 serial port is configured for 9600-8-N-1. SCON is set to Mode 1 (8-bit UART, variable baud rate) with reception enabled, and Timer 1 in Mode 2 (8-bit auto-reload) generates the baud rate. With an 11.0592 MHz crystal, TH1 = 0xFD gives 9600 baud. Characters are written to SBUF, and TI signals that transmission is complete. TXD is P3.1 and RXD is P3.0.

**Pseudocode:**

1. `TMOD = 0x20` (Timer 1, Mode 2).
2. `TH1 = 0xFD` for 9600 baud.
3. `SCON = 0x50` (Mode 1, REN = 1).
4. Start Timer 1: `TR1 = 1`.
5. `uart_tx(c)`: write `SBUF = c`, wait until `TI == 1`, then clear `TI`.
6. `uart_puts(s)`: send each character of the string.
7. Transmit "Hello from 8051" repeatedly to the PC terminal.

**Code Base:**

`uart_init()`, `uart_tx()` and `uart_puts()` form the UART driver. The board is connected to the PC through a USB-to-TTL converter and the output is viewed in PuTTY at 9600 baud.

#### INFERENCE

"Hello from 8051" is continuously displayed on PuTTY, confirming correct UART configuration and baud-rate generation from Timer 1. SBUF is used for transmission and the TI flag indicates when transmission is complete.


### Task B - UART Echo

**Project folder:** [`TASKB_UART_Echo/`](TASKB_UART_Echo/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The UART receive path is added. When a character arrives, the RI flag is set and the received byte is available in SBUF. In the interrupt-driven version, the serial ISR stores each received byte in an RX ring buffer, and the main loop reads from the buffer and transmits the same character back.

**Pseudocode:**

1. Initialise the UART as in Task A and enable the serial interrupt (`ES = 1`, `EA = 1`).
2. In the serial ISR: if `RI` is set, clear RI and store `SBUF` in the ring buffer at `head`.
3. If `TI` is set, clear TI.
4. In the main loop, if `head != tail`, read a character from the buffer.
5. Transmit the character back with `uart_tx()`.
6. Repeat continuously.

**Code Base:**

`void serial_isr(void) interrupt 4` handles RI/TI. A circular buffer (`rx_buf[]`, `head`, `tail`) decouples reception from processing so that no characters are lost.

#### INFERENCE

Whatever is typed in PuTTY (e.g. "Hello 8051") is echoed back by the 8051. This shows that SBUF is used for both transmit and receive, RI indicates a received character, and interrupt-driven reception with a ring buffer makes the driver reliable.
