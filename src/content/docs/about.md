---
title: About ZeroBro
template: splash

lastUpdated: 2025-12-28
head:
  - tag: style
    content: |
      .hero-bg { display: none !important; }
      .content-panel { max-width: 70rem !important; margin: auto; padding:1.5rem 0px !important; }
      #_top{
      text-align: center;
      font-size: 4rem;
      padding-bottom: 3rem;
      }
---

## Introduction

**ZeroBro** is an open-source hardware project designed to be an accessible and versatile multi-tool for geeks, pentesters, and electronics enthusiasts. Built around the powerful and ubiquitous **ESP-WROOM-32** microcontroller, it aims to provide similar functionality to the Flipper Zero but at a fraction of the cost and with a focus on DIY modifiability.

This project is a love letter to the maker community, encouraging users to build, code, and understand their own tools.

## Key Features

- **Core**: ESP-WROOM-32 (Dual-core 240MHz, WiFi + Bluetooth/BLE).
- **Wireless Capabilities**: WiFi scanning, deauth attacks (educational/testing only), Bluetooth packet sniffing, and beacon generated.
- **RFID/NFC**: 125kHz and 13.56MHz reading/emulation (planned).
- **Sub-GHz**: CC1101 module integration for 433/868/915MHz communications (planned).
- **Interface**: OLED display and navigation buttons for standalone operation.
- **Open Source**: All hardware schematics, firmware, and documentation are freely available.

## Philosophy

We believe that hardware security tools should not be behind a paywall. By using common, off-the-shelf components like the ESP32, we ensure that anyone with a soldering iron and some curiosity can build their own ZeroBro. 

> **Disclaimer**: This tool is intended for educational and legal security research purposes only. The authors and project contributors are not responsible for any misuse. Always obtain permission before testing on networks or devices you do not own.
