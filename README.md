# Smart Greenhouse Control System using ESP32 and Blynk

## Overview

The Smart Greenhouse Control System is an IoT-based solution designed to monitor and control environmental conditions inside a greenhouse automatically. The system uses an ESP32 microcontroller to collect real-time data from sensors and control various actuators to maintain optimal growing conditions for plants.

The greenhouse environment is monitored using temperature, humidity, and CO₂ sensors. Based on predefined threshold values, the system automatically controls ventilation, heating, humidification, and lighting. Additionally, all sensor readings and device statuses can be monitored remotely through the Blynk IoT platform.

---

## Features

* Real-time temperature monitoring
* Real-time humidity monitoring
* CO₂ level monitoring
* Automatic fan control for ventilation
* Automatic heater control for temperature regulation
* Automatic misting system control for humidity regulation
* Automatic grow light control
* Remote monitoring using Blynk mobile application
* Wi-Fi connectivity using ESP32
* Automatic Wi-Fi reconnection
* Real-time actuator status updates

---

## System Architecture

```text
+------------------+
|     Blynk App    |
+--------+---------+
         |
         | Wi-Fi
         |
+--------v---------+
|      ESP32       |
+--------+---------+
         |
         |
+--------+-----------------------------+
|                                      |
|  DHT11 Sensor                        |
|  MQ135 CO₂ Sensor                    |
|                                      |
+--------+-----------------------------+
         |
         |
+--------+-----------------------------+
|                                      |
|  Fan                                |
|  Heater                             |
|  Misting System                     |
|  Grow Light                         |
|                                      |
+--------------------------------------+
```

---

## Hardware Components

| Component               | Quantity    |
| ----------------------- | ----------- |
| ESP32 Development Board | 1           |
| DHT11/DHT22 Sensor      | 1           |
| MQ135 CO₂ Sensor        | 1           |
| 4-Channel Relay Module  | 1           |
| DC Fan                  | 1           |
| Heater                  | 1           |
| Ultrasonic Mist Maker   | 1           |
| LED Grow Light          | 1           |
| Jumper Wires            | As Required |
| Power Supply            | 1           |

---

## Software Requirements

* Arduino IDE
* ESP32 Board Package
* Blynk IoT Platform
* Required Libraries:

  * WiFi.h
  * BlynkSimpleEsp32.h
  * DHT.h

---

## Pin Configuration

| Device           | ESP32 Pin |
| ---------------- | --------- |
| DHT11 Sensor     | GPIO 4    |
| Fan Relay        | GPIO 12   |
| Heater Relay     | GPIO 13   |
| Grow Light Relay | GPIO 14   |
| Misting Relay    | GPIO 15   |
| MQ135 CO₂ Sensor | GPIO 34   |

---

## Blynk Dashboard Configuration

Create the following widgets in the Blynk dashboard:

| Widget            | Virtual Pin |
| ----------------- | ----------- |
| Temperature Gauge | V0          |
| Humidity Gauge    | V1          |
| CO₂ Gauge         | V2          |
| Fan Status LED    | V3          |
| Heater Status LED | V4          |
| Mist Status LED   | V5          |
| Light Status LED  | V6          |

---

## Working Principle

### Temperature Control

* If temperature exceeds **30°C**, the fan is activated.
* If temperature falls below **18°C**, the heater is activated.
* If temperature is within the acceptable range, both devices remain off.

### Humidity Control

* If humidity falls below **40%**, the misting system is activated.
* Once the humidity reaches the desired level, the misting system is turned off.

### CO₂ Control

* If the CO₂ level exceeds the predefined threshold, the ventilation fan is activated to improve air circulation.

### Lighting Control

* The grow light operates automatically according to the configured schedule.
* Lights remain ON during daytime simulation and OFF during nighttime simulation.

---

## Installation

### Step 1: Clone the Repository

```bash
git clone https://github.com/your-username/smart-greenhouse-system.git
```

### Step 2: Open the Project

Open the `.ino` file using Arduino IDE.

### Step 3: Install Required Libraries

Install the following libraries from the Arduino Library Manager:

```text
Blynk
DHT Sensor Library
ESP32 Board Package
```

### Step 4: Configure Wi-Fi and Blynk

Update the following variables in the code:

```cpp
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Greenhouse"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";
```

### Step 5: Upload the Code

1. Connect the ESP32 board.
2. Select the correct COM port.
3. Click Upload.

---

## Future Enhancements

* Soil moisture monitoring
* Automated irrigation system
* OLED/LCD local display
* Email and push notifications
* Data logging with Firebase
* Historical data analytics
* AI-based environmental prediction
* Mobile application integration
* Solar-powered greenhouse system

---

## Expected Outcomes

* Improved plant growth conditions
* Reduced manual monitoring effort
* Efficient resource utilization
* Real-time environmental monitoring
* Remote greenhouse management
* Increased crop productivity


---

## License

This project is developed for educational and research purposes. Feel free to modify and extend it according to your project requirements.
