---
title: BadUSB UART Example
description: ESP32 to Arduino Pro Micro communication for HID keyboard emulation
---

# BadUSB UART Communication Example

This example demonstrates UART (serial) communication between an ESP-WROOM-32 and an Arduino Pro Micro, enabling HID (Human Interface Device) keyboard emulation capabilities similar to the USB Rubber Ducky.

## Overview

The system consists of two parts:
1. **ESP32** - Sends commands via UART
2. **Arduino Pro Micro** - Receives commands and emulates a USB keyboard

This allows the ESP32 to control keyboard input on a connected computer, useful for:
- Security testing and penetration testing
- Automation of repetitive tasks
- Educational demonstrations of HID attacks
- Remote keyboard control

## Hardware Requirements

### Required Components
- **ESP-WROOM-32 development board**
- **Arduino Pro Micro** (ATmega32U4-based board)
- **Jumper wires** (3 connections: TX, RX, GND)
- **USB cable** (for programming each board)
- **Target computer** (to connect Arduino Pro Micro via USB)

### Why Arduino Pro Micro?

The Arduino Pro Micro uses the ATmega32U4 microcontroller, which has native USB support. This allows it to:
- Emulate USB keyboards
- Emulate USB mice
- Act as other HID devices
- Appear as a native USB device to the host computer

Regular Arduino boards (like Uno) cannot do this because they use separate USB-to-serial chips.

## Wiring Diagram

Connect ESP32 to Arduino Pro Micro:

| ESP32 Pin | Arduino Pro Micro Pin | Description |
|-----------|----------------------|-------------|
| GPIO 1 (TX) | RX                 | ESP32 transmit to Arduino receive |
| GPIO 0 (RX) | TX                 | ESP32 receive to Arduino transmit |
| GND       | GND                  | Common ground |

**Important:** 
- ESP32 TX (GPIO 1) → Arduino RX
- ESP32 RX (GPIO 0) → Arduino TX
- Both devices must share a common ground

## Architecture

```
┌─────────────────┐         UART          ┌──────────────────┐
│   ESP-WROOM-32  │ ◄──────────────────► │ Arduino Pro Micro│
│                 │   9600 baud           │                  │
│  - WiFi         │                       │  - USB HID       │
│  - BLE          │                       │  - Keyboard      │
│  - Sensors      │                       │  - Mouse         │
└─────────────────┘                       └────────┬─────────┘
                                                   │ USB
                                                   ▼
                                          ┌─────────────────┐
                                          │ Target Computer │
                                          └─────────────────┘
```

## ESP32 Code

### Main Application

Located at: `componets-esp/UART - Arduino Pro Micro/ESP/ZeroBro_main.c`

```c
void app_main(void)
{
    printf("UART ESP32 communicate with Arduino Pro Micro!\n");

    // Configure UART
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_driver_install(UART_NUM_0, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, TXD_PIN, RXD_PIN, 
                 UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    
    // Send data continuously
    char* Txdata = (char*) malloc(100);
    while (1) {
        sprintf(Txdata, "Sending Packet = %d\r\n", num++);
        uart_write_bytes(UART_NUM_0, Txdata, strlen(Txdata));
        vTaskDelay(500);  // Wait 500ms
    }
}
```

### Key Features

- **UART Configuration:** 9600 baud, 8 data bits, no parity
- **Continuous Transmission:** Sends packets every 500ms
- **Simple Protocol:** Text-based commands

## Arduino Code

### Keyboard Emulator

Located at: `componets-esp/UART - Arduino Pro Micro/Arduino/keyboard-injector.ino`

The Arduino code listens for commands and translates them to keystrokes:

```c
void loop() {
    while (Serial1.available()) {
        String a = Serial1.readString();
        Serial.println(a);  // Debug output

        // Process special commands
        if (a == "[SHIFT]") {
            Keyboard.press(KEY_RIGHT_SHIFT);
        } else if (a == "[CTRL]") {
            Keyboard.press(KEY_LEFT_CTRL);
        } else if (a == "[ENTER]") {
            Keyboard.press(KEY_KP_ENTER);
        } else if (a == "[ALT]") {
            Keyboard.press(KEY_LEFT_ALT);
        } else if (a == "[DEL]") {
            Keyboard.press(KEY_DELETE);
        } else if (a == "[TAB]") {
            Keyboard.press(KEY_TAB);
        } else {
            // Type regular characters
            Keyboard.print(a);
        }
    }
}
```

### Supported Commands

| Command | Action |
|---------|--------|
| `[SHIFT]` | Press/release Shift key |
| `[CTRL]` | Press/release Ctrl key |
| `[ALT]` | Press/release Alt key |
| `[ENTER]` | Press Enter key |
| `[DEL]` | Press Delete key |
| `[TAB]` | Press Tab key |
| Regular text | Type the characters |

## Building and Flashing

### ESP32 Side

1. Navigate to project directory:
```bash
cd "componets-esp/UART - Arduino Pro Micro/ESP"
```

2. Build and flash:
```bash
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

### Arduino Side

1. Open Arduino IDE
2. Load `keyboard-injector.ino`
3. Select Board: **Arduino Leonardo** or **Arduino Micro**
4. Select the correct port
5. Upload the sketch

**Note:** The Arduino Pro Micro uses the same bootloader as Leonardo.

## Testing the Setup

### Basic Test

1. **Connect hardware:** Wire ESP32 to Arduino Pro Micro as shown above
2. **Flash ESP32:** Upload the ESP32 code
3. **Flash Arduino:** Upload the Arduino code
4. **Connect Arduino to PC:** Plug Arduino Pro Micro into target computer via USB
5. **Observe:** The Arduino should start typing the messages sent from ESP32

### Expected Behavior

With the default code, you should see the Arduino typing:
```
Sending Packet = 0
Sending Packet = 1
Sending Packet = 2
...
```

Every 500ms on the target computer!

## Customization Ideas

### 1. Send Keyboard Shortcuts

Modify ESP32 to send useful shortcuts:

```c
// Open command prompt on Windows
uart_write_bytes(UART_NUM_0, "[WIN]", 5);
vTaskDelay(100);
uart_write_bytes(UART_NUM_0, "r", 1);
vTaskDelay(100);
uart_write_bytes(UART_NUM_0, "cmd[ENTER]", 10);
```

### 2. WiFi-Controlled Keyboard

Add WiFi control to the ESP32:
- Create a web interface
- Send commands via HTTP requests
- Remote keyboard control over network

### 3. Scripted Attacks

Create predefined keystroke sequences:

```c
void run_script() {
    send_keys("[WIN]r");
    delay(500);
    send_keys("notepad[ENTER]");
    delay(1000);
    send_keys("Hello from ESP32!");
}
```

### 4. Add Authentication

Require a specific command sequence before accepting keyboard commands:

```c
if (authenticated) {
    execute_command(received_data);
}
```

### 5. Implement Ducky Script

Parse and execute Rubber Ducky script format:
```
DELAY 1000
GUI r
DELAY 500
STRING notepad
ENTER
```

## Security Considerations

⚠️ **Important Warnings:**

1. **Legal Use Only:** Use this technology only on systems you own or have explicit permission to test
2. **Responsible Disclosure:** If you discover vulnerabilities, report them responsibly
3. **Educational Purpose:** This project is for learning about hardware security
4. **No Malicious Use:** Creating or deploying malicious keystroke injectors may be illegal

### Defense Against HID Attacks

To protect against unauthorized HID devices:
- Lock your computer when away
- Disable USB ports when not in use
- Use endpoint protection software
- Monitor for unusual USB device connections
- Implement USB port whitelisting policies

## Troubleshooting

### Problem: "Arduino not typing anything"

**Solutions:**
- Verify UART connections (TX to RX, RX to TX)
- Check baud rates match on both sides (9600)
- Ensure common ground connection
- Verify Arduino is properly enumerated as a keyboard (check Device Manager on Windows)

### Problem: "Wrong characters appear"

**Solutions:**
- Check baud rate configuration
- Verify voltage levels (both should be 3.3V or 5V tolerant)
- Ensure clean power supply to both devices
- Check for electrical interference

### Problem: "Arduino not recognized as keyboard"

**Solutions:**
- Ensure you uploaded to Arduino Pro Micro, not regular Arduino
- Select correct board in Arduino IDE (Leonardo/Micro)
- Check USB cable supports data (not just power)
- Try different USB port on target computer

### Problem: "UART communication not working"

**Solutions:**
- Swap TX and RX connections (common mistake)
- Verify both devices share common ground
- Check TX/RX pin assignments in code
- Use a logic analyzer or oscilloscope to verify signals

## Applications

### Penetration Testing
- Simulating USB attack vectors
- Testing endpoint security
- Demonstrating physical access risks

### Automation
- Automating repetitive keyboard tasks
- Remote system configuration
- Automated testing scenarios

### Education
- Teaching about HID protocols
- Understanding USB security
- Demonstrating attack/defense concepts

## Next Steps

- Add Bluetooth control from a smartphone
- Implement payload encryption
- Create a library of useful scripts
- Add display for status feedback
- Implement reverse shell over USB

## Source Code Location

```
componets-esp/UART - Arduino Pro Micro/
├── ESP/                        # ESP32 UART code
│   └── ZeroBro_main.c
├── Arduino/                    # Arduino Pro Micro code
│   └── keyboard-injector.ino
└── README.md                   # Detailed explanation
```

## Additional Resources

- [Arduino Keyboard Library](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/)
- [USB Rubber Ducky Payloads](https://github.com/hak5/usbrubberducky-payloads)
- [ESP-IDF UART Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/uart.html)
- [ATmega32U4 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7766-8-bit-AVR-ATmega16U4-32U4_Datasheet.pdf)

---

**Remember:** With great power comes great responsibility. Use this knowledge ethically and legally! 🔐
