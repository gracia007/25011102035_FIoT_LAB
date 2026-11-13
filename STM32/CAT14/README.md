# CAT14 – BME280 Sensor Interfacing Using I²C and (MQTT) using Custom Built ESP8266 API

| Field | Details |
|---|---|
| **EXP** | CAT14 |
| **DATE** | 27/10/2026 |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I²C and (MQTT) using Custom Built ESP8266 API |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4F, up to 84 MHz), on-board ST-Link, STM32CubeMX + Keil MDK-ARM (HAL), BME280 sensor (I²C), ESP8266 Wi-Fi module, MQTT broker (broker.emqx.io), Node-RED |
| **TASK NO** | Single task – Sensor Interfacing (BME280) – MQTT – Node-RED Analytics |

## 1. Objective

As a continuation of CAT13, interface the BME280 over I²C to obtain compensated temperature, pressure and humidity, publish the readings as JSON over MQTT using the custom-built ESP8266 library (`ESPLib.c`, `ESPLib.h`), and receive them in Node-RED (MQTT-in node) to visualise the three parameters and compute minimum, maximum and average statistics.

## 2. Circuit Diagram

<img width="1331" height="672" alt="430E1EA0-B662-428D-B465-AEFF131EAAA1_1_201_a" src="https://github.com/user-attachments/assets/f9f3add0-35d4-4c92-91ae-3e067bf0d7e0" />


**Pin Connections:**

| Signal / Component | MCU Pin | Description |
|---|---|---|
| 3.3 V / GND | 3V3 / GND | Board supply from USB (ST-Link) |
| Clock | HSI 16 MHz / ST-Link MCO 8 MHz → PLL 84 MHz | System clock (configured in CubeMX) |
| BME280 SCL | PB8 (I2C1_SCL) | I²C clock |
| BME280 SDA | PB9 (I2C1_SDA) | I²C data |
| BME280 VCC / GND | 3V3 / GND | Sensor power |
| BME280 SDO | GND | I²C address 0x76 |
| BME280 CSB | 3V3 | Selects I²C mode |
| USART2 TX / RX | PA2 / PA3 | ST-Link virtual COM port (PC terminal) |
| ESP8266 TX / RX | PA10 / PA9 (USART1) | Wi-Fi module UART |
| ESP8266 VCC / GND | 3V3 / GND | Wi-Fi module power |

## 3. Core Logic / Pseudocode / Code Base

**Working Principle:**

The custom ESPLib wraps the AT commands needed for Wi-Fi and MQTT: `ESP8266_Init()`, `ESP8266_wifiConnect()`, `ESP8266_portConnect()` (TCP to the broker on port 1883), `MQTT_connectBroker()` and `MQTT_publishTopic()`. `MQTTTimer()` is called from `SysTick_Handler()` to maintain the keep-alive timing. Node-RED subscribes to the same topic, parses the JSON and displays/aggregates the values.

**Pseudocode:**

1. Initialise HAL, I2C1, UARTs and the BME280 (as in CAT13).
2. `ESP8266_Init(StationMode, huart)` and `ESP8266_wifiConnect(SSID, password)`.
3. `ESP8266_portConnect("TCP", "broker.emqx.io", "1883")`.
4. Fill `MQTT_InitTypeDef_t` (keepAlive = 500, CleanSession, clientID) and call `MQTT_connectBroker()`.
5. Loop: read BME280 → build JSON `{"status":"success","temperature":..,"humidity":..,"pressure":..}`.
6. `MQTT_publishTopic(topic, json, QoS0)` every second.
7. Node-RED: MQTT-in (same topic) → JSON node → gauges/charts and a function node computing min/max/average.

**Code Base:**

`MQTTTimer()` is added under `USER CODE BEGIN SysTick_IRQn 0`. Wi-Fi credentials and broker address are replaced with placeholders in the submitted code.

**Node-RED Statistics (example format):**

| Parameter | Minimum | Maximum | Average |
|---|---|---|---|
| Temperature (°C) | 27.91 | 29.02 | 28.46 |
| Humidity (%RH) | 59.80 | 64.20 | 62.15 |
| Pressure (hPa) | 1007.84 | 1009.31 | 1008.56 |


## 4. Inference

**Observation:**

The STM32 published a JSON message every second; Node-RED received it through the MQTT-in node and displayed live temperature, humidity and pressure, and computed their minimum, maximum and average.

**Conclusion:**

MQTT provides lightweight publish/subscribe communication between the sensor node and the analytics platform, completing the IoT flow: sensor → STM32 → ESP8266 → MQTT broker → Node-RED.
