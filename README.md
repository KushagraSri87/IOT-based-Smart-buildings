# ⚡ Energy Consumption Optimization in Smart Buildings
### IoT-Based Smart Building Automation Using Arduino UNO & ESP8266

An IoT-based smart building project designed to monitor environmental conditions, detect human occupancy, and automate electrical appliances to improve energy efficiency. The system integrates sensors, Arduino UNO, an ESP8266 Wi-Fi module, and cloud-based monitoring to enable real-time environmental tracking and intelligent appliance control.

---

## 📌 Overview

Energy consumption in buildings can be reduced by automating electrical appliances according to occupancy and environmental conditions.

This project implements a smart building monitoring and automation system using an **Arduino UNO, DHT11 temperature and humidity sensor, PIR motion sensor, and a relay module**.

The system detects human presence, monitors room temperature and humidity, and controls lighting and fans based on predefined conditions. An LCD displays real-time sensor readings and system status, while the ESP8266 Wi-Fi module enables IoT connectivity for remote monitoring through platforms such as ThingSpeak or Blynk.

The project demonstrates how IoT and embedded systems can be used to develop energy-efficient and automated building environments.

## ✨ Key Features

- 🌡️ **Temperature & Humidity Monitoring:** Measures indoor environmental conditions using the DHT11 sensor.
- 🚶 **Occupancy Detection:** Uses a PIR sensor to detect human movement and presence.
- 💡 **Automatic Lighting Control:** Controls lights based on occupancy detection.
- 🌀 **Smart Fan Control:** Automates fan operation according to predefined temperature thresholds.
- 📟 **Real-Time LCD Display:** Displays sensor readings and appliance status on a 16×2 LCD.
- ☁️ **IoT Cloud Integration:** Sends sensor data to ThingSpeak or Blynk for remote monitoring, depending on the configured platform.
- 🔌 **Relay-Based Switching:** Controls electrical appliances through a 2-channel relay module.
- ⚡ **Energy Efficiency:** Aims to reduce unnecessary electricity consumption through automated appliance control.
- 🚀 **Future-Ready Design:** Can be extended with data analytics, energy usage prediction, and AI-based optimization.

## 🛠️ Hardware Requirements

| Component | Purpose |
|---|---|
| Arduino UNO | Main microcontroller for sensor processing and control logic |
| ESP8266 Wi-Fi Module | Provides Wi-Fi connectivity for IoT communication |
| DHT11 Sensor | Measures temperature and humidity |
| PIR Motion Sensor | Detects human movement |
| 2-Channel Relay Module | Switches lights and fans |
| 16×2 LCD Display | Displays sensor readings and system status |
| Jumper Wires | Connects the electronic components |
| Breadboard | Supports circuit prototyping |
| Power Supply | Powers the microcontroller and connected modules |
| Light and Fan Loads | Demonstrate automated appliance control |

*Note: Component quantities, wiring, and power requirements may vary depending on the circuit implementation.*

## 💻 Software & Technologies

- **Programming Language:** Embedded C/C++ for Arduino
- **Microcontroller Platform:** Arduino UNO
- **IoT Connectivity:** ESP8266 Wi-Fi
- **Cloud Platforms:** ThingSpeak / Blynk, depending on implementation
- **Sensor Integration:** DHT11 and PIR sensor
- **Display Interface:** 16×2 LCD
- **Appliance Control:** Relay-based switching
- **Development Environment:** Arduino IDE

## 🏗️ System Architecture

The system follows a sensor-to-controller-to-actuator architecture with an optional cloud monitoring layer.

```text
       ┌─────────────────────────┐
       │       DHT11 Sensor      │
       │  Temperature & Humidity │
       └────────────┬────────────┘
                    │
                    ▼
       ┌─────────────────────────┐
       │      Arduino UNO        │
       │                         │
       │  Sensor Data Processing │
       │  Automation Logic       │
       └───────┬─────────┬───────┘
               │         │
       ┌───────▼────┐  ┌─▼────────────────┐
       │ PIR Sensor │  │ 16×2 LCD Display  │
       │ Occupancy  │  │ Live System Data  │
       └────────────┘  └───────────────────┘
               │
               ▼
       ┌─────────────────────────┐
       │    2-Channel Relay      │
       │                         │
       │  Light and Fan Control  │
       └─────────────────────────┘

       Arduino UNO / ESP8266
                  │
                  ▼
       ┌─────────────────────────┐
       │    Wi-Fi Connectivity   │
       └────────────┬────────────┘
                    │
                    ▼
       ┌─────────────────────────┐
       │   IoT Cloud Platform    │
       │ ThingSpeak / Blynk      │
       └─────────────────────────┘
```

*The diagram represents the logical system architecture. The exact wiring and communication arrangement depend on the implemented circuit.*

## ⚙️ How It Works

### 1. Environmental Monitoring
The DHT11 sensor measures room temperature and humidity. The Arduino UNO reads the sensor values and uses them in the automation logic.

### 2. Occupancy Detection
The PIR sensor detects movement within the monitored area. Its output helps determine whether the lighting should be switched on or off according to the configured control logic.

### 3. Automatic Appliance Control
The Arduino evaluates the sensor inputs and controls the relay module.

- **Lighting:** Can be switched on when occupancy is detected and switched off when the area is unoccupied, subject to the configured delay or control logic.
- **Fan:** Can be activated when the temperature exceeds a predefined threshold and deactivated when the temperature falls below the configured limit.

These conditions are configurable according to the requirements of the building.

### 4. Real-Time Data Display
The 16×2 LCD displays the available sensor readings and appliance status, allowing users to observe system operation locally.

### 5. IoT-Based Remote Monitoring
The ESP8266 provides Wi-Fi connectivity for sending sensor readings to a configured IoT cloud platform. Users can monitor the available data remotely through the corresponding dashboard.

### 6. Energy Consumption Optimization
Automated control helps avoid unnecessary appliance operation when the relevant conditions do not require it. Actual energy savings depend on appliance power ratings, occupancy patterns, temperature settings, and the effectiveness of the control logic.

## 🔌 Circuit & Connections

The exact pin assignments should match the circuit and source code in this repository.

A typical connection plan includes:

| Component | Arduino Interface |
|---|---|
| DHT11 Sensor | Digital input |
| PIR Sensor | Digital input |
| Relay Module | Two digital output pins |
| 16×2 LCD | Digital interface or I²C interface, depending on the module |
| ESP8266 | Serial communication or another supported interface |

**Important:** ESP8266 modules use 3.3 V logic and have specific power requirements. Ensure proper voltage compatibility and a suitable power supply before connecting the module.

When switching mains-powered lights or fans, use appropriately rated, enclosed relay hardware and follow electrical safety precautions. Do not handle exposed mains wiring while the system is powered.

## 🚀 Getting Started

Follow these steps to set up the project.

### Prerequisites

Install the following software:

- Arduino IDE
- Appropriate Arduino board support
- Required sensor, LCD, and communication libraries
- An ESP8266 configuration compatible with your hardware
- A ThingSpeak or Blynk account if cloud monitoring is enabled

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/KushagraSri87/IOT-based-Smart-buildings.git
```

**2. Navigate to the project directory**

```bash
cd IOT-based-Smart-buildings
```

**3. Open the Arduino project**

Open the project's
