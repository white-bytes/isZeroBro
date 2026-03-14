# Development Workflow

This project consists of two distinct parts:
1.  **Web Frontend**: Built with [Astro](https://astro.build).
2.  **Firmware**: ESP32 components using [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/).

## 1. Web Frontend (Astro)

The web interface is located in the root directory.

### Setup
Install dependencies:
```bash
yarn install
```

### Development Server
Start the local development server:
```bash
yarn dev
```
Access the site at `http://localhost:4321`.

## 2. Firmware (ESP32)

The firmware code is located in `componets-esp/`.
Specifically, `componets-esp/Wifi/WifiScanner` is an **ESP-IDF** project (indicated by `CMakeLists.txt`).

### Prerequisite
You need the **ESP-IDF** tools installed.
*   **VS Code**: Install the "Espressif IDF" extension.
*   **CLI**: Follow ESP-IDF installation guide.

### Building & Flashing (CLI)
Navigate to the component directory:
```bash
cd "componets-esp/Wifi/WifiScanner"
```

Set the target (first time only):
```bash
idf.py set-target esp32
```

Build, Flash, and Monitor:
```bash
idf.py build flash monitor
```

### Using PlatformIO (Alternative)
Since you have `pio` installed, you can also use PlatformIO.
You will need to create a `platformio.ini` file in `componets-esp/Wifi/WifiScanner` to use it with PlatformIO.

Example `platformio.ini`:
```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = espidf
monitor_speed = 115200
```
Then use:
```bash
pio run -t upload
pio device monitor
```
