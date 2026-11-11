# CAT6 – Task A – UART Initialization and Character Transmission

| Field | Details |
|---|---|
| **EXP** | CAT6 |
| **DATE** | 17/08/2026 |
| **NAME OF EXP** | UART Driver and Serial Debugging |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, USB-to-TTL serial converter, PC with PuTTY |
| **TASK NO** | Task A – UART Initialization and Character Transmission |

## 1. Objective

Configure the 8051 UART for 8-bit UART mode, asynchronous operation, 9600 baud, 1 stop bit and no parity. Transmit "Hello from 8051" continuously to a PC terminal (8051 → USB-to-TTL → PC → PuTTY).

## 2. Circuit Diagram

<img width="1600" height="1000" alt="WhatsApp Image 2026-11-11 at 10 06 03" src="https://github.com/user-attachments/assets/b144dcf4-caf7-4639-a262-44cdc6e12a00" />


**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| TXD | P3.1 | To RX of USB-to-TTL converter |
| RXD | P3.0 | From TX of USB-to-TTL converter |
| GND | GND | Common ground with USB-to-TTL converter |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

TXD (P3.1) and RXD (P3.0) have the alternate function of the serial port. SCON selects Mode 1 (8-bit UART, variable baud rate) and REN enables reception. Timer 1 in Mode 2 (8-bit auto-reload) generates the baud rate: Baud = 11.0592 MHz / (12 × 32 × (256 − TH1)), so TH1 = 0xFD (253) gives 9600 baud. A character is sent by writing to SBUF; the TI flag is set when transmission completes.

**Pseudocode:**

1. `TMOD = 0x20` – Timer 1, Mode 2 (auto-reload).
2. `TH1 = 0xFD` – reload value for 9600 baud.
3. `SCON = 0x50` – Mode 1, REN = 1.
4. `TR1 = 1` – start Timer 1.
5. `uart_tx(c)`: `SBUF = c;` wait `while(!TI);` then `TI = 0;`.
6. `uart_puts(s)`: call `uart_tx()` for each character.
7. In `while(1)`: send "Hello from 8051\r\n" with a short delay.

**Code Base:**

```c
void uart_init(void) { TMOD = 0x20; TH1 = 0xFD; SCON = 0x50; TR1 = 1; }
void uart_tx(char c)  { SBUF = c; while (!TI); TI = 0; }
void uart_puts(char *s) { while (*s) uart_tx(*s++); }
```

**Register Summary:**

| Register | Value | Purpose |
|---|---|---|
| SCON | 0x50 | Mode 1 (8-bit UART), REN = 1 |
| TMOD | 0x20 | Timer 1, Mode 2 auto-reload |
| TH1 | 0xFD | 9600 baud at 11.0592 MHz |
| SBUF | – | Transmit/receive data buffer |
| TI / RI | – | Transmit complete / receive complete flags |


## 4. Inference

**Observation:**

PuTTY (9600, 8-N-1) continuously displayed "Hello from 8051". Transmitting one known character first confirmed the configuration before sending full strings.

**Conclusion:**

The serial port works in Mode 1 with Timer 1 as the baud-rate generator. SBUF holds the data and TI indicates completed transmission, forming the basis of a UART driver.
