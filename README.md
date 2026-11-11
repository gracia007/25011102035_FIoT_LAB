# 25011102035 - Foundations of IoT Lab (25CS2741)

Lab experiment submissions for **25CS2741 Fundamentals of Internet of Things + Lab**, organised by hardware platform.
Experiment numbers (CATn) follow the **Hands-on exercises numbering in the coursework**, one folder per week.

## Repository Structure

```
25011102035_FIoT_LAB/
├── README.md
├── .gitignore
├── 8051/
│   └── CAT2 ... CAT7
└── STM32/
    └── CAT8 ... CAT14

Experiment with multiple tasks          Experiment with a single task
CATn/                                   CATn/
├── README.md   (overview)              ├── README.md   (full documentation)
├── TASKA_<name>/                       ├── circuit.png
│   ├── README.md (full documentation)  └── project files
│   ├── circuit.png
│   └── project files
└── TASKB_<name>/ ...
```

Every experiment/task README contains: EXP, DATE, NAME OF EXP, HARDWARE SETUP / PLATFORM, TASK NO, Objective, Circuit Diagram (with pin connections), Core Logic / Pseudocode / Code Base, and Inference.

## Experiment Index

| EXP | Platform | Name of Experiment | Folder |
|---|---|---|---|
| CAT2 | 8051 (AT89S52) | GPIO - Bare-Metal LED Blink | [8051/CAT2](8051/CAT2) |
| CAT3 | 8051 (AT89S52) | Timer-Based LED Pattern Generator and Button Interrupt Controller | [8051/CAT3](8051/CAT3) |
| CAT4 | 8051 (AT89S52) | Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display | [8051/CAT4](8051/CAT4) |
| CAT5 | 8051 (AT89S52) | Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control | [8051/CAT5](8051/CAT5) |
| CAT6 | 8051 (AT89S52) | UART Driver and Serial Debugging | [8051/CAT6](8051/CAT6) |
| CAT7 | 8051 (AT89S52) | 16x2 LCD Driver Development and Dynamic Display Control | [8051/CAT7](8051/CAT7) |
| CAT8 | STM32 Cortex-M3 | STM32 GPIO Bring-Up and Switch-Controlled LED | [STM32/CAT8](STM32/CAT8) |
| CAT9 | STM32 Cortex-M3 | STM32 UART Command Controlled LED | [STM32/CAT9](STM32/CAT9) |
| CAT10 | STM32 Cortex-M3 + ESP8266 | STM32-Wemos Wi-Fi Modem Interface Using AT Commands | [STM32/CAT10](STM32/CAT10) |
| CAT11 | STM32 Cortex-M3 + ESP8266 | STM32 Cortex M3 + ESP8266 HTTP Server | [STM32/CAT11](STM32/CAT11) |
| CAT12 | STM32 Cortex-M4 | STM32F401RE Cortex-M4: GPIO and User Input Programming | [STM32/CAT12](STM32/CAT12) |
| CAT13 | STM32 Cortex-M4 | BME280 Sensor Interfacing Using I2C and Bosch Sensor API | [STM32/CAT13](STM32/CAT13) |
| CAT14 | STM32 Cortex-M4 | BME280 Sensor Interfacing Using I2C and (MQTT) using Custom Built ESP8266 API | [STM32/CAT14](STM32/CAT14) |

## Project Files

- **8051:** Embedded C source (`.c`), Keil project (`.uvproj`), `STARTUP.A51`, compiled firmware (`.hex`).
- **STM32:** CubeMX config (`.ioc`), `Core/`, `Drivers/`, Keil project (`.uvprojx`), compiled firmware (`.hex`).

Build outputs and per-user IDE settings are excluded via [.gitignore](.gitignore).
