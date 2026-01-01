# Building isZeroBro Firmware from Source

This guide will walk you through setting up your development environment to build and flash the isZeroBro ESP32 firmware using Visual Studio Code and CMake.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Installing ESP-IDF](#installing-esp-idf)
- [Setting Up Visual Studio Code](#setting-up-visual-studio-code)
- [Building the Firmware](#building-the-firmware)
- [Flashing to ESP32](#flashing-to-esp32)
- [Project Components](#project-components)
- [Troubleshooting](#troubleshooting)

---

## Prerequisites

Before you begin, ensure you have the following:

### Hardware
- ESP32 development board
- USB cable for programming
- (Optional) RFID RC522 module for RFID reader component
- (Optional) Arduino Pro Micro for BadUSB component

### Software
- **Visual Studio Code** - [Download here](https://code.visualstudio.com/)
- **Git** - [Download here](https://git-scm.com/downloads)
- **Python 3.8 or later** - [Download here](https://www.python.org/downloads/)
- **CMake 3.5 or later** - [Download here](https://cmake.org/download/)

---

## Installing ESP-IDF

ESP-IDF is Espressif's official IoT Development Framework for the ESP32.

### Windows

1. Download the ESP-IDF installer from [Espressif's website](https://dl.espressif.com/dl/esp-idf/)
2. Run the installer and follow the setup wizard
3. The installer will:
   - Install ESP-IDF tools
   - Set up Python environment
   - Configure system PATH variables
4. Verify installation by opening a command prompt and running:
   ```bash
   idf.py --version
   ```

### Linux/macOS

1. Install prerequisites:
   ```bash
   # Ubuntu/Debian
   sudo apt-get update
   sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

   # macOS
   brew install cmake ninja dfu-util
   ```

2. Clone ESP-IDF:
   ```bash
   mkdir -p ~/esp
   cd ~/esp
   git clone --recursive https://github.com/espressif/esp-idf.git
   cd esp-idf
   git checkout v5.1.2  # or latest stable version
   ```

3. Run the install script:
   ```bash
   ./install.sh esp32
   ```

4. Set up environment variables (add to your `~/.bashrc` or `~/.zshrc`):
   ```bash
   alias get_idf='. $HOME/esp/esp-idf/export.sh'
   ```

5. Activate ESP-IDF environment:
   ```bash
   get_idf
   ```

---

## Setting Up Visual Studio Code

### Install Extensions

1. Open Visual Studio Code
2. Install the following extensions:
   - **C/C++** (Microsoft)
   - **ESP-IDF** (Espressif)
   - **CMake Tools** (Microsoft)

### Configure ESP-IDF Extension

1. Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on macOS) to open the command palette
2. Type "ESP-IDF: Configure ESP-IDF Extension"
3. Select "Express" installation or choose "Advanced" to specify ESP-IDF path
4. Select your ESP-IDF version and installation path
5. Wait for the configuration to complete

### Verify Setup

1. Open the Command Palette (`Ctrl+Shift+P`)
2. Type "ESP-IDF: Show Examples Projects"
3. If you see example projects, your setup is correct

---

## Building the Firmware

The isZeroBro project contains multiple ESP32 components. Each component can be built separately.

### Clone the Repository

```bash
git clone https://github.com/white-bytes/isZeroBro.git
cd isZeroBro
```

### Select a Component to Build

The project includes several components in the `componets-esp` directory:

- **WiFi Scanner** - Scans and displays nearby WiFi networks
- **RFID Reader** - Reads RFID tags using RC522 module
- **UART Communication** - Communicates with Arduino Pro Micro for BadUSB functionality

### Build WiFi Scanner

1. Open VS Code:
   ```bash
   cd componets-esp/Wifi/WifiScanner
   code .
   ```

2. Configure the project:
   - Press `Ctrl+Shift+P` and run "ESP-IDF: Set Espressif Device Target"
   - Select `esp32` (or your specific ESP32 variant)

3. Build using VS Code:
   - Press `Ctrl+Shift+P` and run "ESP-IDF: Build your Project"
   - Or click the Build button in the bottom status bar
   - Or use the terminal:
     ```bash
     idf.py build
     ```

4. The build output will be in the `build/` directory

### Build Other Components

For RFID Reader:
```bash
cd componets-esp/SPI\ -\ RFID\ reader/ESP
idf.py build
```

---

## Flashing to ESP32

### Using VS Code

1. Connect your ESP32 to your computer via USB
2. Press `Ctrl+Shift+P` and run "ESP-IDF: Select Port to Use"
3. Choose your ESP32's COM port (e.g., `COM3` on Windows or `/dev/ttyUSB0` on Linux)
4. Flash the firmware:
   - Press `Ctrl+Shift+P` and run "ESP-IDF: Flash your Project"
   - Or click the Flash button in the bottom status bar
   - Or use the terminal:
     ```bash
     idf.py -p PORT flash
     ```
   Replace `PORT` with your device's port (e.g., `COM3` or `/dev/ttyUSB0`)

### Monitor Serial Output

To view the serial output from your ESP32:

1. In VS Code:
   - Press `Ctrl+Shift+P` and run "ESP-IDF: Monitor Device"
   - Or click the Monitor button in the status bar

2. Or use the command line:
   ```bash
   idf.py -p PORT monitor
   ```

3. To exit the monitor, press `Ctrl+]`

### Flash and Monitor in One Command

```bash
idf.py -p PORT flash monitor
```

---

## Project Components

### WiFi Scanner

Located in `componets-esp/Wifi/WifiScanner/`

**Features:**
- Scans for nearby WiFi access points
- Displays SSID, RSSI, encryption type, and channel
- Uses ESP32's built-in WiFi capabilities

**Pin Configuration:**
- No external pins required (uses internal WiFi)

### RFID Reader

Located in `componets-esp/SPI - RFID reader/ESP/`

**Features:**
- Reads RFID tags using RC522 module
- Displays tag serial numbers
- Uses SPI communication

**Pin Configuration:**
- MISO: GPIO 19
- MOSI: GPIO 23
- SCK: GPIO 18
- SDA: GPIO 5

### UART Communication (BadUSB)

Located in `componets-esp/UART - Arduino Pro Micro/`

**Features:**
- Communicates with Arduino Pro Micro
- Enables keystroke injection capabilities
- Uses UART serial communication

**Pin Configuration:**
- TXD: GPIO 1
- RXD: GPIO 0

---

## Troubleshooting

### Common Issues

#### "idf.py: command not found"
**Solution:** Make sure you've activated the ESP-IDF environment:
```bash
# Linux/macOS
. $HOME/esp/esp-idf/export.sh

# Windows
%userprofile%\esp\esp-idf\export.bat
```

#### "Port not found" or "Failed to connect"
**Solutions:**
- Check that your ESP32 is connected via USB
- Verify the correct driver is installed (CP210x or CH340)
- Try a different USB cable or port
- On Linux, add your user to the dialout group:
  ```bash
  sudo usermod -a -G dialout $USER
  ```
  Then log out and log back in

#### "CMake Error: The source directory does not appear to contain CMakeLists.txt"
**Solution:** Make sure you're in the correct component directory. Each component has its own CMakeLists.txt file.

#### Build fails with Python errors
**Solution:** Ensure you're using Python 3.8 or later:
```bash
python --version
```

#### Permission denied on Linux/macOS
**Solution:** Add your user to the appropriate group:
```bash
sudo usermod -a -G dialout $USER
```

#### "Toolchain not found"
**Solution:** Reinstall ESP-IDF tools:
```bash
cd ~/esp/esp-idf
./install.sh esp32
```

### Getting Help

If you encounter issues not covered here:

1. Check the [ESP-IDF documentation](https://docs.espressif.com/projects/esp-idf/en/latest/)
2. Visit the [isZeroBro GitHub Issues](https://github.com/white-bytes/isZeroBro/issues)
3. Join the ESP32 community forums

---

## Additional Resources

- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [VSCode ESP-IDF Extension Documentation](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md)

---

## Contributing

For more information about contributing to the isZeroBro project, please refer to the main [README.md](README.md).
