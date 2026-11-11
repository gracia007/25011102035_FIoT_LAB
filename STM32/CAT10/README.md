# CAT10 – STM32–Wemos Wi-Fi Modem Interface Using AT Commands

| Field | Details |
|---|---|
| **EXP** | CAT10 |
| **DATE** | 05/10/2026 |
| **NAME OF EXP** | STM32–Wemos Wi-Fi Modem Interface Using AT Commands |
| **HARDWARE SETUP / PLATFORM** | STM32F103C8T6 Blue Pill (ARM Cortex-M3, 72 MHz), ST-Link V2, STM32CubeMX + Keil MDK-ARM (HAL), Wemos D1 Mini (ESP8266) Wi-Fi module, USB-to-TTL converter |
| **TASK NO** | Task A – Establish STM32 ↔ Wemos UART Communication (PDF: Task 9A), Task B – Explore the ESP8266 AT Command Interface (PDF: Task 9B), Task C – Connect Wemos to Wi-Fi (PDF: Task 9C) |

## Overview

Interface the STM32 with a Wemos D1 Mini (ESP8266) through UART, configure the Wi-Fi modem using AT commands, and connect it to a Wi-Fi network. Two UARTs are used: one for STM32 ↔ Wemos (AT commands and responses) and one for STM32 ↔ PC (debug display). Note: the questions PDF labels these tasks 9A–9C; they are stored here as Tasks A–C of CAT10 as per the coursework numbering.

## Tasks

| Task | Folder | Description |
|---|---|---|
| Task A – Establish STM32 ↔ Wemos UART Communication (PDF: Task 9A) | [`TASKA_STM32_Wemos_UART_Communication/`](TASKA_STM32_Wemos_UART_Communication/) | Send AT from STM32, show Wemos reply OK on the PC |
| Task B – Explore the ESP8266 AT Command Interface (PDF: Task 9B) | [`TASKB_ESP8266_AT_Command_Interface/`](TASKB_ESP8266_AT_Command_Interface/) | Identify AT commands for each requirement and record responses |
| Task C – Connect Wemos to Wi-Fi (PDF: Task 9C) | [`TASKC_Connect_Wemos_to_WiFi/`](TASKC_Connect_Wemos_to_WiFi/) | Station mode, join AP, report mode/status/IP on PC |

Each task folder contains its own `README.md` (objective, circuit diagram, core logic and inference), `circuit.png` and the project files.
