# CAT6 – UART Driver and Serial Debugging

| Field | Details |
|---|---|
| **EXP** | CAT6 |
| **DATE** | 17/08/2026 |
| **NAME OF EXP** | UART Driver and Serial Debugging |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, USB-to-TTL serial converter, PC with PuTTY |
| **TASK NO** | Task A – UART Initialization and Character Transmission, Task B – UART Echo |

## Overview

Develop an interrupt-driven UART driver for the 8051 that communicates with a PC terminal through a USB-to-TTL serial interface. The UART is configured for 9600-8-N-1, and character transmission and reception are demonstrated using PuTTY. The driver implements transmit and receive functions followed by an interrupt-driven RX ring buffer.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task A – UART Initialization and Character Transmission | [`TASKA_UART_Init_and_Char_Transmission/`](TASKA_UART_Init_and_Char_Transmission/) | 9600-8-N-1 UART setup, transmit "Hello from 8051" continuously |
| Task B – UART Echo | [`TASKB_UART_Echo/`](TASKB_UART_Echo/) | Interrupt-driven RX ring buffer; every typed character is echoed back |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
