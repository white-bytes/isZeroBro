# isZeroBro Project

An open-source ESP32-based multi-tool for wireless security research, IoT prototyping, and electronics education.

[Project Documentation](https://wordparticles.monday.com/docs/18393297026?blockId=e0432743-ee66-4fbe-a01a-e185f61f07ee)

## Purpose
> [!IMPORTANT]
> This project is a work in progress and is not yet ready for production use. I am building this out of curiosity and
> hope to learn more network security and how to protect against other like-minded individuals. 🌈 😎.

## 🚀 Getting Started with ESP-WROOM-32

### Best Example for Beginners: WiFi Scanner ⭐

**New to ESP32 development?** Start here!

The **WiFi Scanner** is the recommended example to begin your ESP-WROOM-32 journey:
- ✅ No external hardware needed
- ✅ Works with just your ESP32 board
- ✅ Immediate results you can see
- ✅ Teaches fundamental ESP32 concepts

**👉 [View WiFi Scanner Documentation](./src/content/docs/esp32-examples/wifi-scanner.md)**

### Available Examples

1. **[WiFi Scanner](./componets-esp/Wifi/WifiScanner/)** ⭐ **RECOMMENDED**
   - Scan and analyze WiFi networks
   - Perfect for beginners
   - [Full Documentation](./src/content/docs/esp32-examples/wifi-scanner.md)

2. **[RFID Reader](./componets-esp/SPI%20-%20RFID%20reader/)**
   - Read RFID tags with RC522 module
   - Requires: RC522 RFID module
   - [Full Documentation](./src/content/docs/esp32-examples/rfid-reader.md)

3. **[BadUSB UART](./componets-esp/UART%20-%20Arduino%20Pro%20Micro/)**
   - Keyboard emulation via Arduino Pro Micro
   - Requires: Arduino Pro Micro board
   - [Full Documentation](./src/content/docs/esp32-examples/badusb-uart.md)

## 📖 Documentation

Comprehensive guides are available in the [ESP32 Examples Documentation](./src/content/docs/esp32-examples/) directory:
- Hardware requirements
- Wiring diagrams
- Build instructions
- Code explanations
- Troubleshooting guides
- Customization ideas

## 🛠️ Quick Start

```bash
# Install ESP-IDF (if not already installed)
# See: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/

# Navigate to an example (WiFi Scanner recommended)
cd componets-esp/Wifi/WifiScanner/

# Build the project
idf.py build

# Flash to your ESP32
idf.py -p /dev/ttyUSB0 flash monitor
```

## 📁 Repository Structure

```
isZeroBro/
├── componets-esp/              # ESP32 example code
│   ├── Wifi/WifiScanner/      # WiFi Scanner (Recommended) ⭐
│   ├── SPI - RFID reader/     # RFID Reader example
│   └── UART - Arduino Pro Micro/  # BadUSB example
├── src/content/docs/          # Documentation site
│   └── esp32-examples/        # ESP32 guides
└── README.md                  # This file
```

## 🎯 Project Goals

- Create a versatile, affordable, open-source hardware security research tool
- Democratize access to hardware pentesting education
- Build on the accessible ESP-WROOM-32 platform
- Empower makers, students, and security researchers

## ⚠️ Responsible Use

This project is for:
- ✅ Educational purposes
- ✅ Authorized security testing
- ✅ Personal learning and experimentation
- ✅ Ethical research

**Always obtain proper authorization before testing on systems you don't own.**

## 🤝 Contributing

Contributions are welcome! Whether it's:
- Bug fixes
- New examples
- Documentation improvements
- Feature suggestions

## 📄 License

MIT License - See LICENSE file for details

---

TODO [ZERO-2]: Update more details.
