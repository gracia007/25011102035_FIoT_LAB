# CAT14 - BME280 Sensor Interfacing Using I2C and (MQTT) using Custom Built ESP8266 API

| Field | Details |
|---|---|
| **EXP** | CAT14 |
| **DATE** | 27/10/2026 |
| **NAME OF EXP** | BME280 Sensor Interfacing Using I2C and (MQTT) using Custom Built ESP8266 API |
| **HARDWARE SETUP / PLATFORM** | NUCLEO-F401RE (STM32F401RE, ARM Cortex-M4), on-board ST-Link, STM32CubeMX + Keil MDK, BME280 sensor (I2C), ESP8266 Wi-Fi module, MQTT broker, Node-RED |
| **TASK NO** | Single task (no subdivisions in the questions PDF) |

## Circuit Diagram

![Circuit Diagram](circuit.png)

## Core Logic / Pseudocode / Code Base

**Working Principle:**

As a continuation of CAT13, the compensated BME280 readings are published to an MQTT broker using the custom ESP8266 library (`ESPLib.c`, `ESPLib.h`). The ESP8266 connects to Wi-Fi and to the broker on port 1883, and Node-RED subscribes to the topic to display and analyse the data.

**Pseudocode:**

1. Initialise the HAL, I2C1, USART2 and the BME280 (as in CAT13).
2. `ESP8266_Init(StationMode, huart2)` and `ESP8266_wifiConnect(SSID, password)`.
3. `ESP8266_portConnect("TCP", broker, "1883")`.
4. Fill `MQTT_InitTypeDef_t` (keepAlive, CleanSession, clientID) and call `MQTT_connectBroker()`.
5. In `while(1)`, read the BME280 and format the values as a string/JSON.
6. Publish with `MQTT_publishTopic(topic, payload, QoS0)` every second.
7. In Node-RED, use an MQTT-in node subscribed to the topic, parse the JSON and show it on dashboard gauges/charts.

**Code Base:**

`MQTTTimer()` is called from `SysTick_Handler()` for keep-alive timing. Wi-Fi credentials and broker address are replaced with placeholders in the submitted code.

## INFERENCE

The sensor readings were published to the MQTT broker and displayed live in Node-RED, demonstrating an end-to-end IoT flow: sensor → STM32 → ESP8266 → MQTT broker → Node-RED analytics.
