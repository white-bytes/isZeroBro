# isZeroBro ESP32 Examples

This directory contains example code for the ESP-WROOM-32 microcontroller.

## 🌟 Best Example to Start: WiFi Scanner

**New to ESP32?** Start with the **[WiFi Scanner](./Wifi/WifiScanner)** example!

It's the recommended starting point because:
- ✅ No external hardware required
- ✅ Immediate visual feedback
- ✅ Demonstrates core ESP32 concepts
- ✅ Well-structured ESP-IDF project

## 📚 Complete Documentation

**For detailed guides, hardware requirements, building instructions, and troubleshooting, visit:**

👉 **[ESP32 Examples Documentation](../src/content/docs/esp32-examples/)**

The documentation includes:
- [**WiFi Scanner** - Recommended Starting Point](../src/content/docs/esp32-examples/wifi-scanner.md)
- [**RFID Reader** - SPI Communication](../src/content/docs/esp32-examples/rfid-reader.md)
- [**BadUSB UART** - HID Keyboard Emulation](../src/content/docs/esp32-examples/badusb-uart.md)

## Available Examples

### 1. WiFi Scanner ⭐ RECOMMENDED
**Path:** `Wifi/WifiScanner/`

Scan nearby WiFi access points and display network information.

**Features:**
- WiFi scanning capabilities
- ESP-IDF framework basics
- FreeRTOS integration
- NVS storage handling

### 2. RFID Reader
**Path:** `SPI - RFID reader/ESP/`

Interface with RC522 RFID module to read tags.

**Features:**
- SPI communication
- Event-driven architecture
- RFID tag detection

**Requirements:** RC522 RFID module, RFID tags

### 3. BadUSB (UART Communication)
**Path:** `UART - Arduino Pro Micro/ESP/`

Communicate with Arduino Pro Micro for HID keyboard emulation.

**Features:**
- UART serial communication
- Keyboard injection capabilities
- Command protocol

**Requirements:** Arduino Pro Micro board

---

## Quick Start

1. **Install ESP-IDF:** Follow the [official installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)

2. **Navigate to an example:**
   ```bash
   cd Wifi/WifiScanner/
   ```

3. **Build and flash:**
   ```bash
   idf.py build
   idf.py -p /dev/ttyUSB0 flash monitor
   ```

## Need Help?

📖 Read the [complete documentation](../src/content/docs/esp32-examples/) for:
- Detailed setup instructions
- Hardware wiring diagrams
- Code explanations
- Troubleshooting guides
- Customization ideas

## Hardware Design

- [PCB Design](PCB Design)

TODO [ZERO-3]: update with actual design details.