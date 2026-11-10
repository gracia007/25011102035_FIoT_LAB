# CAT11 - STM32 Cortex M3 + ESP8266 HTTP Server

> Note: No separate questions PDF was issued for this week; it continues CAT10. Confirm the task details with the evaluator.

| Field | Details |
|---|---|
| **EXP** | CAT11 |
| **DATE** | <!-- fill in --> |
| **NAME OF EXP** | STM32 Cortex M3 + ESP8266 HTTP Server |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 (Blue Pill, ARM Cortex-M3), ST-Link debugger, STM32CubeMX + Keil MDK, Wemos D1 Mini (ESP8266) |
| **TASK NO** | <!-- confirm with evaluator --> |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Core Logic / Pseudocode / Code Base

**Working Principle:**

Continuing from CAT10, the ESP8266 is configured as a TCP server on port 80. When a browser sends an HTTP request to the module's IP address, the request arrives at the STM32 as `+IPD`. The STM32 builds an HTTP response (status line, headers and body) and sends it back using `AT+CIPSEND`, then closes the connection.

**Pseudocode:**

1. Connect the ESP8266 to Wi-Fi as in CAT10 and read its IP with `AT+CIFSR`.
2. Enable multiple connections: `AT+CIPMUX=1`.
3. Start the server: `AT+CIPSERVER=1,80`.
4. Wait for `+IPD,<id>,...` from a browser request.
5. Build the response: `HTTP/1.1 200 OK`, `Content-Type`, `Content-Length` (calculated with `strlen()` of the body) and the body.
6. Send `AT+CIPSEND=<id>,<length>`, wait for '>', then send the response.
7. Close the connection with `AT+CIPCLOSE=<id>` and repeat.

**Code Base:**

The HTTP response is constructed with `snprintf()`, and `Content-Length` is computed from the actual body length so the browser parses the response correctly.

## INFERENCE

Opening the module's IP address in a browser displayed the response sent by the STM32, showing that the STM32 + ESP8266 can work as a simple HTTP server using raw AT commands.
