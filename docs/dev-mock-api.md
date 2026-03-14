# Mock Scan Endpoint

File: `src/pages/scan.ts`

## Purpose
This file functions as a **Mock API Endpoint** for the local development environment. It intercepts requests to `/scan` which would otherwise fail (404) because the actual ESP32 web server is not present locally.

## Functionality
- **Route**: `GET /scan`
- **Behavior**: Returns a static JSON array of mock WiFi networks.
- **Data Structure**: Matches the `AP` interface expected by the frontend:
  ```typescript
  interface AP {
    ssid: string;
    rssi: number;
    channel: number;
    auth: string;
  }
  ```

## Why it's needed
Allows the UI development (`yarn dev`) to proceed and display data without flashing to the hardware.
