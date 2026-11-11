# CAT2 – Task 1 – Hardware Board Bring-Up

| Field | Details |
|---|---|
| **EXP** | CAT2 |
| **DATE** | 20/07/2026 |
| **NAME OF EXP** | 8051 Tool Chain Setup – Development Board – AT89S52 (GPIO Interfacing) |
| **HARDWARE SETUP / PLATFORM** | AT89S52 (8051 core) development board, 11.0592 MHz crystal, Keil uVision C51, ISP programmer, on-board user LED |
| **TASK NO** | Task 1 – Hardware Board Bring-Up |

## 1. Objective

Identify the microcontroller, debugger/programmer, power source, user LED and the relevant GPIO pin. Verify the board's power rails using a digital multimeter, identify the LED GPIO port and pin from the datasheet/schematic, and establish communication between the host computer and the target MCU.

## 2. Circuit Diagram

![Circuit Diagram](circuit.png)

**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| VCC | +5 V | Board supply |
| GND | GND | Common ground |
| XTAL1 / XTAL2 | 11.0592 MHz crystal | System clock (1 machine cycle ≈ 1.085 µs) |
| User LED | P1.0 | On-board LED (confirm from board schematic) |
| ISP (MOSI/MISO/SCK/RST) | P1.5 / P1.6 / P1.7 / RST | In-system programming interface |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

Before writing firmware, the hardware must be verified. The board schematic and the AT89S52 pin diagram are used to locate the MCU, the programming interface, the power input and the user LED. A multimeter confirms that VCC and GND are correct, and a test program is flashed to confirm that the host PC can program the target.

**Pseudocode:**

1. Identify the MCU (AT89S52) and its CPU core (8-bit 8051).
2. Identify the programmer/debug interface (ISP) and the power source.
3. Measure the supply voltage between VCC (pin 40) and GND (pin 20) with a multimeter.
4. Locate the user LED and trace its port and pin on the schematic.
5. Determine whether the LED is active-HIGH or active-LOW.
6. Connect the programmer, build a test program in Keil and flash the generated `.hex` file.
7. Record the values in the Hardware Bring-Up Sheet.

**Code Base:**

This task does not contain application logic. The results are recorded in the bring-up sheet below.

**Hardware Bring-Up Sheet:**

| Parameter | Student Entry |
|---|---|
| MCU | AT89S52 |
| CPU Core | 8-bit 8051 (MCS-51) |
| Operating Voltage | 5 V |
| Debug Interface | ISP (SPI-based in-system programming) |
| LED GPIO Port | Port 1 |
| LED GPIO Pin | P1.0 |
| LED Active State | Active-LOW (LED ON when pin = 0) |
| LED Frequency (Hz) | ≈ 1 Hz (Task 2) |


## 4. Inference

**Observation:**

The board powered up correctly with about 5 V measured between VCC and GND. The LED port/pin and its active level were identified from the schematic, and the test program was flashed successfully from the host PC.

**Conclusion:**

The hardware and toolchain (Keil uVision + ISP programmer) are working, so the board is ready for bare-metal firmware development.
