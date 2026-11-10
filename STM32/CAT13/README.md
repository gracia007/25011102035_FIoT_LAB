# CAT13 - BME280 Sensor Interfacing Using I2C and Bosch Sensor API

| Field | Details |
|---|---|
| **EXP** | CAT13 |
| **DATE** | 23/10/2026 |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I2C and Bosch Sensor API |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4), on-board ST-Link, STM32CubeMX + Keil MDK, BME280 sensor (I2C), ESP8266 Wi-Fi module |
| **TASK NO** | Single task (no subdivisions in the questions PDF) |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Core Logic / Pseudocode / Code Base

**Working Principle:**

The BME280 sensor is interfaced over I2C1 (address 0x76) using the Bosch Sensortec BME280 Sensor API (`bme280.c`, `bme280.h`, `bme280_defs.h`). User I2C read/write and delay functions built on HAL are passed to the API, which reads the raw registers and applies Bosch compensation to give temperature, pressure and humidity. The values are printed over UART and served as a JSON HTTP response through the ESP8266.

**Pseudocode:**

1. Initialise the HAL, I2C1, the debug UART and the ESP8266 UART.
2. Set up the `bme280_dev` structure with `user_i2c_read`, `user_i2c_write` and `user_delay_us`.
3. Call `bme280_init()` (reads the chip ID 0x60 and the calibration data).
4. Configure oversampling and filter, then set normal mode.
5. Every second, call `bme280_get_sensor_data()` to get compensated values.
6. Print Temperature (°C), Pressure (hPa) and Humidity (%RH) on the UART terminal.
7. Build the JSON string with `snprintf()`, calculate `Content-Length` with `strlen()`, and send the HTTP response via `AT+CIPSEND`.

**Code Base:**

`HAL_I2C_Mem_Read()` / `HAL_I2C_Mem_Write()` implement the Bosch API interface functions. Pressure is converted from Pa to hPa. The JSON payload is `{"status":"success","temperature":..,"humidity":..,"pressure":..}`.

## INFERENCE

The correct chip ID was read and compensated temperature, pressure and humidity values were displayed; the values changed appropriately when the sensor environment changed. The browser received the readings as JSON, showing a complete sensor → STM32 → Wi-Fi → HTTP data path.
