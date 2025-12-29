---
title: WiFi Scanner - Best Example for ESP-WROOM-32
description: Complete guide to the WiFi Scanner example - the recommended starting point for ESP32 development
---

# WiFi Scanner Example

**⭐ Recommended as the best starting example for ESP-WROOM-32!**

The WiFi Scanner is an excellent introduction to ESP32 development. It scans for nearby WiFi access points and displays detailed information about each network, including SSID, signal strength (RSSI), encryption type, and channel.

## Why This is the Best Starting Example

1. **No External Hardware Required** - Works with just your ESP-WROOM-32 board
2. **Immediate Results** - Instantly see WiFi networks in your area
3. **Comprehensive** - Demonstrates multiple ESP32 features in one example
4. **Well-Structured** - Follows ESP-IDF best practices with proper project layout
5. **Educational** - Teaches fundamental concepts you'll use in other projects

## What You'll Learn

- 📡 **WiFi Station Mode** - How to use ESP32's WiFi capabilities
- 🔄 **FreeRTOS Tasks** - Understanding ESP32's operating system
- 💾 **NVS (Non-Volatile Storage)** - Initializing persistent storage
- 📊 **Event Handling** - Working with ESP32's event loop
- 🔐 **Security Analysis** - Understanding WiFi encryption types

## Hardware Requirements

### Required
- **ESP-WROOM-32 development board** (ESP32 DevKit, NodeMCU-32S, or similar)
- **USB cable** (micro-USB or USB-C, depending on your board)
- **Computer** with ESP-IDF installed

### No Additional Components Needed!
This example works standalone - perfect for beginners.

## Software Prerequisites

### 1. Install ESP-IDF

Follow the [official ESP-IDF installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) for your operating system.

**Recommended version:** ESP-IDF v4.4 or later

### 2. Set Up Environment

```bash
# Linux/macOS
. $HOME/esp/esp-idf/export.sh

# Windows
%userprofile%\esp\esp-idf\export.bat
```

## Project Structure

```
componets-esp/Wifi/WifiScanner/
├── CMakeLists.txt              # Main CMake configuration
├── main/
│   ├── main.c                  # Application entry point
│   └── CMakeLists.txt          # Main component CMake
└── components/
    └── Scanner/
        ├── wifi_scanner.c      # WiFi scanning implementation
        ├── wifi_scanner.h      # WiFi scanner header
        └── CMakeLists.txt      # Scanner component CMake
```

## Code Overview

### Main Application (`main/main.c`)

The main application initializes the system and calls the WiFi scanner:

```c
void app_main() {
    // Initialize NVS (required for WiFi)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    
    // Perform WiFi scan
    int count = 0;
    wifi_ap_record_t* ap_info = wifiScan(&count);
    
    // Display results
    ESP_LOGI(TAG, "AP Detect: \t\t%d", count);
    
    if (ap_info != NULL) {
        for (int i = 0; i < count; i++) {
            ESP_LOGI(TAG, "SSID:\t\t%s", (char*)ap_info[i].ssid);
            ESP_LOGI(TAG, "RSSI:\t\t%d", ap_info[i].rssi);
            ESP_LOGI(TAG, "Channel \t\t%d", ap_info[i].primary);
            // ... display encryption info
        }
        free(ap_info);
    }
}
```

### Key Functions

#### `wifiScan(int* count)`
- Initializes WiFi in station mode
- Starts a WiFi scan
- Returns an array of discovered access points
- Updates `count` with the number of APs found

#### `cipherType()` and `cipherGroup()`
- Helper functions to decode WiFi encryption methods
- Returns human-readable encryption type strings

## Building and Flashing

### Step 1: Navigate to Project Directory

```bash
cd componets-esp/Wifi/WifiScanner
```

### Step 2: Configure the Project (Optional)

```bash
idf.py menuconfig
```

You can customize settings like:
- Serial flasher config
- CPU frequency
- WiFi settings

### Step 3: Build the Project

```bash
idf.py build
```

This compiles the code and generates the firmware binary.

### Step 4: Connect Your ESP32

Connect your ESP-WROOM-32 board to your computer via USB.

### Step 5: Flash and Monitor

Flash the firmware and open the serial monitor in one command:

```bash
idf.py -p /dev/ttyUSB0 flash monitor
```

**Note:** Replace `/dev/ttyUSB0` with your actual port:
- Linux: Usually `/dev/ttyUSB0` or `/dev/ttyACM0`
- macOS: Usually `/dev/cu.usbserial-*` or `/dev/cu.SLAB_USBtoUART`
- Windows: Usually `COM3`, `COM4`, etc.

To find your port:
```bash
# Linux/macOS
ls /dev/tty.*

# Or use idf.py to auto-detect
idf.py -p PORT flash monitor
```

### Step 6: View the Results

After flashing, the serial monitor will display output like:

```
I (320) MAIN: AP Detect: 		12
I (320) MAIN: SSID:		MyHomeNetwork
I (320) MAIN: RSSI:		-45
I (320) MAIN: Type: 		CCMP
I (320) MAIN: Group: 		CCMP
I (320) MAIN: Channel 		6
I (330) MAIN: SSID:		CoffeeShop_WiFi
I (330) MAIN: RSSI:		-67
I (330) MAIN: Type: 		CCMP
I (330) MAIN: Group: 		CCMP
I (330) MAIN: Channel 		11
...
```

## Understanding the Output

### SSID
The network name of the access point.

### RSSI (Received Signal Strength Indicator)
Signal strength in dBm. Typical values:
- **-30 to -50 dBm:** Excellent signal
- **-50 to -60 dBm:** Good signal
- **-60 to -70 dBm:** Fair signal
- **-70 to -80 dBm:** Weak signal
- **Below -80 dBm:** Very weak signal

### Encryption Type (Type & Group)
Common values:
- **TKIP:** Older WPA encryption (less secure)
- **CCMP:** Modern WPA2/WPA3 encryption (recommended)
- **WEP:** Very old, insecure encryption (avoid)

### Channel
The WiFi channel (1-14 for 2.4 GHz). Channels 1, 6, and 11 are non-overlapping in most regions.

## Customization Ideas

Once you understand the basic example, try these modifications:

### 1. Filter by Signal Strength
Only display networks with RSSI > -60 dBm:

```c
if (ap_info[i].rssi > -60) {
    ESP_LOGI(TAG, "SSID:\t\t%s", (char*)ap_info[i].ssid);
    // ... display info
}
```

### 2. Sort by Signal Strength
Sort the access points by RSSI before displaying.

### 3. Continuous Scanning
Add a loop to scan every few seconds:

```c
while(1) {
    wifi_ap_record_t* ap_info = wifiScan(&count);
    // ... display results
    vTaskDelay(pdMS_TO_TICKS(5000)); // Wait 5 seconds
}
```

### 4. Add BSSID Display
Show the MAC address of each access point:

```c
ESP_LOGI(TAG, "BSSID:\t\t%02x:%02x:%02x:%02x:%02x:%02x",
         ap_info[i].bssid[0], ap_info[i].bssid[1],
         ap_info[i].bssid[2], ap_info[i].bssid[3],
         ap_info[i].bssid[4], ap_info[i].bssid[5]);
```

### 5. Export to JSON
Format the output as JSON for easier parsing by other tools.

## Troubleshooting

### Problem: "No serial data received"

**Solution:**
- Check USB cable connection
- Verify correct port selection with `idf.py -p PORT monitor`
- Try pressing the BOOT or EN button during flashing
- Check USB drivers are installed for your board's chip (CP2102, CH340, etc.)

### Problem: "Build fails with missing header files"

**Solution:**
- Ensure ESP-IDF environment is properly sourced
- Run `. $HOME/esp/esp-idf/export.sh` (or Windows equivalent)
- Verify ESP-IDF version compatibility (v4.4+)

### Problem: "No access points found (count = 0)"

**Solution:**
- Ensure your ESP32 antenna is properly connected (if external)
- Check if WiFi is disabled in `menuconfig`
- Verify you're in an area with WiFi networks
- Increase scan timeout in the scanner code

### Problem: "Permission denied on /dev/ttyUSB0"

**Solution (Linux):**
```bash
sudo usermod -a -G dialout $USER
# Log out and log back in for changes to take effect
```

### Problem: "ESP32 keeps rebooting"

**Solution:**
- Check power supply - USB ports may not provide enough current
- Try a different USB cable or powered USB hub
- Check for short circuits on your board

## Next Steps

After mastering the WiFi Scanner, you can:

1. **Explore More Examples**
   - [RFID Reader](./rfid-reader) - Learn SPI communication
   - [BadUSB UART](./badusb-uart) - Explore serial communication

2. **Extend This Example**
   - Add WiFi connection capability
   - Create a web server to display scan results
   - Implement deauthentication detection
   - Build a WiFi analyzer with channel usage graphs

3. **Learn ESP32 Features**
   - Bluetooth scanning
   - Web server creation
   - Deep sleep modes
   - GPIO control

## Source Code Location

The complete source code for this example is located in:
```
componets-esp/Wifi/WifiScanner/
```

## Additional Resources

- [ESP-IDF WiFi API Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html)
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
- [ESP32 Community Forum](https://esp32.com/)

---

**Happy coding! This WiFi Scanner example provides a solid foundation for your ESP-WROOM-32 journey.** 🚀
