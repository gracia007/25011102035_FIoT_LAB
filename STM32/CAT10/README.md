# CAT10 - STM32-Wemos Wi-Fi Modem Interface Using AT Commands

| Field | Details |
|---|---|
| **EXP** | CAT10 |
| **DATE** | 05/10/2026 |
| **NAME OF EXP** | STM32-Wemos Wi-Fi Modem Interface Using AT Commands |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill, ARM Cortex-M3), ST-Link debugger, STM32CubeMX + Keil MDK, Wemos D1 Mini (ESP8266), USB-to-TTL converter |
| **TASK NO** | Task A - Establish STM32 <-> Wemos UART Communication (PDF: Task 9A), Task B - Explore the ESP8266 AT Command Interface (PDF: Task 9B), Task C - Connect Wemos to Wi-Fi (PDF: Task 9C) |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Tasks

### Task A - Establish STM32 <-> Wemos UART Communication (PDF: Task 9A)

**Project folder:** [`TASKA_STM32_Wemos_UART_Communication/`](TASKA_STM32_Wemos_UART_Communication/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

Two UARTs are used: USART2 (PA2 TX, PA3 RX) connects the STM32 to the Wemos D1 Mini (ESP8266), and a second UART connects the STM32 to the PC for debugging. TX and RX are cross-connected and the boards share a common ground. The STM32 sends `AT\r\n` to the Wemos and forwards the reply to the PC terminal.

**Pseudocode:**

1. Initialise the HAL, USART2 (Wemos) and the PC UART at the same baud rate as the ESP8266 (115200).
2. Send "AT\r\n" to the Wemos.
3. Receive the response characters ('O', 'K', '\r', '\n') from the Wemos.
4. Forward the response to the PC terminal.
5. Display ">> AT" and "<< OK" in PuTTY.

**Code Base:**

`HAL_UART_Transmit(&huart2, ...)` sends AT commands, `HAL_UART_Receive()` with a timeout collects the response, and the response is re-transmitted on the PC UART.

#### INFERENCE

The Wemos replied "OK" to the AT command, and the reply was shown on the PC terminal, confirming that UART communication between the STM32 and the ESP8266 works.


### Task B - Explore the ESP8266 AT Command Interface (PDF: Task 9B)

**Project folder:** [`TASKB_ESP8266_AT_Command_Interface/`](TASKB_ESP8266_AT_Command_Interface/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The ESP8266 AT-command interface is explored by sending commands from the STM32 and recording the replies. Each requirement is mapped to the matching AT command.

**Pseudocode:**

1. Check modem response: `AT`.
2. Check firmware/version: `AT+GMR`.
3. Set Wi-Fi station mode: `AT+CWMODE=1`.
4. Scan available networks: `AT+CWLAP`.
5. Connect to an AP: `AT+CWJAP="SSID","password"`.
6. Obtain network information: `AT+CIFSR`.
7. Establish a TCP connection: `AT+CIPSTART="TCP","<ip>",<port>`.
8. Send application data: `AT+CIPSEND=<length>`, then the data.

**Code Base:**

A helper `send_at(cmd, timeout)` transmits a command, waits for the reply and prints both on the PC terminal so each command can be studied.

#### INFERENCE

Each AT command produced the expected response (OK, version information, list of networks, IP address, etc.), showing how the ESP8266 is configured and controlled entirely through text commands over UART.


### Task C - Connect Wemos to Wi-Fi (PDF: Task 9C)

**Project folder:** [`TASKC_Connect_Wemos_to_WiFi/`](TASKC_Connect_Wemos_to_WiFi/)

#### Core Logic / Pseudocode / Code Base

**Working Principle:**

The STM32 firmware configures the ESP8266 as a Wi-Fi station and connects it to the local network using a sequence of AT commands. Each step waits for the expected response before continuing, and the final status is reported on the PC terminal.

**Pseudocode:**

1. Send `AT` and wait for OK.
2. Send `AT+CWMODE=1` to set station mode.
3. Send `AT+CWJAP="SSID","password"` and wait for "WIFI CONNECTED", "WIFI GOT IP" and OK.
4. Send `AT+CIFSR` to query the IP address.
5. Print WIFI MODE : STATION, WIFI STATUS : CONNECTED and IP ADDRESS : xxx.xxx.xxx.xxx on the PC terminal.

**Code Base:**

The connection sequence is a series of `send_at()` calls with response checking using `strstr()`. The Wi-Fi credentials are replaced with placeholders in the submitted code.

#### INFERENCE

The ESP8266 connected to the Wi-Fi network and received an IP address, which was reported on the PC terminal. The STM32 can therefore control the Wi-Fi modem through AT commands and bring the node onto the network.
