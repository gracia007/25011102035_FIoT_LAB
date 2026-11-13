# CAT6 – Task B – UART Echo

| Field | Details |
|---|---|
| **EXP** | CAT6 |
| **DATE** | 17/08/2026 |
| **NAME OF EXP** | UART Driver and Serial Debugging |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, USB-to-TTL serial converter, PC with PuTTY |
| **TASK NO** | Task B – UART Echo |

## 1. Objective

Make the experiment interactive: whatever character is typed in PuTTY must be returned by the 8051 (PC → 8051 → PC). For example, typing "Hello 8051" must display "Hello 8051".

## 2. Circuit Diagram

<img width="1600" height="1000" alt="WhatsApp Image 2026-11-11 at 10 06 03" src="https://github.com/user-attachments/assets/f367d3ad-eae0-401b-8a21-b5d5e93487d7" />

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

When a character is received, the RI flag in SCON is set and the byte is available in SBUF (the same SFR address is used for both transmit and receive buffers). With the serial interrupt enabled, the ISR stores each received byte in a circular RX buffer; the main loop reads bytes from the buffer and transmits them back, so no characters are lost even when typing fast.

**Pseudocode:**

1. Initialise the UART as in Task A.
2. Enable the serial interrupt: `ES = 1; EA = 1;`.
3. Serial ISR: if `RI` → clear RI, store SBUF in `rx_buf[head]`, advance `head`.
4. Serial ISR: if `TI` → clear TI.
5. Main loop: while `head != tail`, read `rx_buf[tail]`, advance `tail`.
6. Transmit the character back with `uart_tx()`.
7. Repeat continuously.

**Code Base:**

```c
void serial_isr(void) interrupt 4 {
    if (RI) { RI = 0; rx_buf[head] = SBUF; head = (head + 1) % BUF_SIZE; }
    if (TI) { TI = 0; }
}
```

## 4. Inference

**Observation:**

Every character typed in PuTTY was echoed back immediately; typing "Hello 8051" and "ABC123" displayed the same text on the terminal.

**Conclusion:**

RI signals a received character and SBUF holds it. Interrupt-driven reception with a ring buffer decouples receiving from processing and makes the UART driver reliable.
