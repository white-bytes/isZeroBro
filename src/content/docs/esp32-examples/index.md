---
title: ESP32 Examples Overview
description: Get started with ESP-WROOM-32 development using these example projects
---

# ESP32 Examples for ESP-WROOM-32

Welcome to the ZeroBro ESP32 examples collection! This section provides comprehensive guides for various ESP-WROOM-32 projects included in this repository.

## Available Examples

### 🌐 [WiFi Scanner](./wifi-scanner) - **Recommended Starting Point**

The WiFi Scanner is the **best example to get started** with ESP-WROOM-32 development. This example demonstrates:

- **WiFi scanning capabilities** - Scan and detect nearby access points
- **ESP-IDF framework basics** - Learn proper project structure
- **FreeRTOS integration** - Understand task management
- **NVS (Non-Volatile Storage)** - Handle persistent data
- **No external hardware required** - Works with just the ESP32 board

**Why start here?**
- Complete and well-structured codebase
- Immediate visual feedback (see WiFi networks)
- Teaches fundamental ESP32 concepts
- Easy to verify it's working correctly

### 📡 [RFID Reader](./rfid-reader)

Read RFID tags using the RC522 module via SPI communication.

**Requirements:** RC522 RFID module, RFID tags

### ⌨️ [BadUSB - UART Communication](./badusb-uart)

Communicate with an Arduino Pro Micro to enable HID keyboard emulation.

**Requirements:** Arduino Pro Micro board

---

## Getting Started

1. **Choose an example** - We recommend starting with the [WiFi Scanner](./wifi-scanner)
2. **Check hardware requirements** - Ensure you have the necessary components
3. **Follow the build instructions** - Each example includes detailed setup steps
4. **Experiment and learn** - Modify the code to understand how it works

## Prerequisites

All examples require:
- **ESP-WROOM-32 development board**
- **ESP-IDF** (Espressif IoT Development Framework) installed
- **USB cable** for programming and power
- **Basic knowledge of C programming**

## Need Help?

- Check the troubleshooting section in each example guide
- Review the [ESP-IDF documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)
- Explore the code in the `componets-esp/` directory of this repository
