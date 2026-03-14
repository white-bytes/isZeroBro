---
title: RFID Reader Example
description: Read RFID tags using the RC522 module with ESP-WROOM-32
---

# RFID Reader Example

This example demonstrates how to interface an RC522 RFID module with the ESP-WROOM-32 via SPI communication to read RFID tags.

## Overview

The RFID Reader example uses the RC522 module to:
- Detect RFID tags in proximity
- Read tag serial numbers
- Handle RFID events
- Log tag information to the serial monitor

## Hardware Requirements

### Required Components
- **ESP-WROOM-32 development board**
- **RC522 RFID reader module**
- **RFID tags or cards** (13.56 MHz)
- **Jumper wires** (7 connections needed)
- **Breadboard** (optional, for easier connections)

### Wiring Diagram

Connect the RC522 module to ESP32 using SPI:

| RC522 Pin | ESP32 GPIO | Description |
|-----------|------------|-------------|
| SDA       | GPIO 5     | Chip Select |
| SCK       | GPIO 18    | SPI Clock   |
| MOSI      | GPIO 23    | Master Out  |
| MISO      | GPIO 19    | Master In   |
| IRQ       | Not used   | -           |
| GND       | GND        | Ground      |
| RST       | GPIO 4*    | Reset       |
| 3.3V      | 3.3V       | Power       |

*Note: RST pin configuration may vary based on the RC522 library version. Check the code or library documentation.

## Key Features

### SPI Communication
Demonstrates proper SPI configuration and data transfer.

### Event-Driven Architecture
Uses ESP-IDF's event loop system for handling RFID events:

```c
static void rc522_handler(void* arg, esp_event_base_t base, 
                         int32_t event_id, void* event_data)
{
    rc522_event_data_t* data = (rc522_event_data_t*) event_data;

    switch(event_id) {
        case RC522_EVENT_TAG_SCANNED: {
            rc522_tag_t* tag = (rc522_tag_t*) data->ptr;
            ESP_LOGI(TAG, "Tag scanned (sn: %" PRIu64 ")", tag->serial_number);
        }
        break;
    }
}
```

### Hardware Abstraction
The code uses a library to simplify RFID operations.

## Code Structure

```
componets-esp/SPI - RFID reader/ESP/
├── ZeroBro_main.c              # Main application
└── lib/
    ├── rc522.c                 # RC522 driver implementation
    └── rc522.h                 # RC522 driver header
```

## Building and Flashing

### Navigate to Project Directory
```bash
cd "componets-esp/SPI - RFID reader/ESP"
```

### Configure (if using ESP-IDF)
If the project uses ESP-IDF (you may need to create a CMakeLists.txt):

```bash
idf.py menuconfig
```

### Build
```bash
idf.py build
```

### Flash and Monitor
```bash
idf.py -p /dev/ttyUSB0 flash monitor
```

## Expected Output

When you scan an RFID tag near the RC522 reader, you should see:

```
I (1234) rc522-demo: Tag scanned (sn: 1234567890)
```

Each tag has a unique serial number that identifies it.

## Understanding the Configuration

```c
rc522_config_t config = {
    .spi.host = VSPI_HOST,      // Use VSPI hardware
    .spi.miso_gpio = 19,        // MISO pin
    .spi.mosi_gpio = 23,        // MOSI pin
    .spi.sck_gpio = 18,         // Clock pin
    .spi.sda_gpio = 5,          // Chip select pin
};
```

### VSPI vs HSPI
ESP32 has two SPI peripherals:
- **HSPI** - Usually used for flash memory
- **VSPI** - Available for external devices (used here)

## Customization Ideas

### 1. Store Authorized Tags
Create a whitelist of authorized tag serial numbers:

```c
uint64_t authorized_tags[] = {1234567890, 9876543210};

bool is_authorized(uint64_t tag_sn) {
    for (int i = 0; i < sizeof(authorized_tags)/sizeof(authorized_tags[0]); i++) {
        if (authorized_tags[i] == tag_sn) {
            return true;
        }
    }
    return false;
}
```

### 2. Add Visual Feedback
Connect an LED to indicate tag status:
- Green LED: Authorized tag
- Red LED: Unauthorized tag

### 3. Control a Relay
Use the RFID reader to control access:
```c
if (is_authorized(tag->serial_number)) {
    gpio_set_level(RELAY_PIN, 1);  // Unlock door
    vTaskDelay(pdMS_TO_TICKS(3000));
    gpio_set_level(RELAY_PIN, 0);  // Lock door
}
```

### 4. Log to SD Card
Record all tag scans with timestamps to an SD card.

### 5. Web Interface
Create a web server to display recent tag scans and manage authorized tags.

## Troubleshooting

### Problem: "No tag detected"

**Solutions:**
- Verify all wiring connections
- Check RC522 module power (needs stable 3.3V)
- Ensure tag is close enough (< 5cm)
- Try different RFID tags
- Verify SPI pins are not used by other peripherals

### Problem: "Wrong tag serial number"

**Solution:**
- Some tags may need multiple reads for stability
- Implement debouncing logic
- Check RC522 antenna quality

### Problem: "SPI initialization failed"

**Solution:**
- Verify GPIO pins are available and not conflicting
- Check if another device is using VSPI
- Ensure proper pin configuration in code

### Problem: "Module not responding"

**Solution:**
- Check 3.3V power supply
- Verify RST pin connection and configuration
- Try resetting the ESP32
- Check for loose connections

## Applications

This RFID example can be used for:
- **Access Control Systems** - Unlock doors with authorized tags
- **Attendance Tracking** - Log employee check-ins
- **Asset Management** - Track equipment with RFID tags
- **Payment Systems** - Simple cashless payment terminals
- **Inventory Management** - Track items in storage

## Next Steps

- Combine with WiFi to send tag data to a server
- Add a display to show tag information
- Implement tag writing capabilities
- Create a multi-factor authentication system (RFID + PIN)

## Source Code Location

```
componets-esp/SPI - RFID reader/
├── ESP/                        # ESP32 code
│   ├── ZeroBro_main.c
│   └── lib/
└── README.md                   # Detailed explanation
```

## Additional Resources

- [RC522 Datasheet](https://www.nxp.com/docs/en/data-sheet/MFRC522.pdf)
- [ESP-IDF SPI Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html)
- [RFID Technology Overview](https://en.wikipedia.org/wiki/Radio-frequency_identification)

---

**Note:** This example requires external hardware. If you're new to ESP32, we recommend starting with the [WiFi Scanner](./wifi-scanner) example first.
