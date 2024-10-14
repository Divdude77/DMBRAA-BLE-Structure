# DMBRAA-004 BLE Communication Protocol

## Overview
This document outlines the reverse-engineered BLE communication payloads used to control DMBRAA-004 LED strip lights.

## Objective
The goal was to automate control of these [affordable LED strip lights](https://www.amazon.co.uk/dp/B085L3D7RD?ref=ppx_yo2ov_dt_b_fed_asin_title), which are controlled via Bluetooth Low Energy (BLE) through the [illumiHome app](https://apps.apple.com/gb/app/illumihome/id1529383058). The objective was to enable HomeKit integration using an ESP32, leveraging the HomeSpan and NimBLE libraries. BLE communication was reverse-engineered by capturing and analyzing Bluetooth HCI snoop logs on an Android device using Wireshark.

## Device Advertisement
The BLE device advertises itself with the following parameters:
```
Device Name: DMRRBA-004
Device UUID: E4E655CE-A660-E8FC-75AA-BE1C3603F019
```

## BLE Communication Details
Control of the lights (e.g., toggling, changing colours, adjusting brightness) is achieved by interacting with the following BLE service and characteristic:
```
Service UUID: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
Characteristic UUID: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E
```

### Light Toggle Command
The lights can be toggled on/off via a 4-byte payload. The state (on/off) is represented by a boolean value in the last byte.
```
 Byte | Value
-------------
  1   | 0x5A                    // Command header
  2   | 0x01                    // Toggle command
  3   | 0x02                    // Reserved
  4   | 0x01 (ON) | 0x00 (OFF)  // State
```

### Colour Change Command
To change the colour of the lights, a 6-byte payload is used, with the RGB values encoded in the last three bytes.
```
 Byte | Value
-------------
  1   | 0x5A          // Command header
  2   | 0x07          // Color change command
  3   | 0x01          // Reserved
  4   | Red (uint8)   // Red value (0-255)
  5   | Green (uint8) // Green value (0-255)
  6   | Blue (uint8)  // Blue value (0-255)
```

### Brightness Adjustment Command
Brightness is modified using a 5-byte payload, although the exact encoding of the brightness values is not fully deciphered.
```
 Byte | Value
-------------
  1   | 0x5A  // Command header
  2   | 0x03  // Brightness adjustment command
  3   | 0x01  // Reserved
  4   | ??    // Unknown encoding for brightness level
  5   | ??    // Unknown encoding for brightness level
```
Although the brightness encoding could not be determined, it was ultimately unnecessary for the project, as HomeKit uses HSL (Hue, Saturation, Lightness) values. These were converted to RGB values for control purposes.

## Additional Notes
This reverse-engineering effort identifies the core functionality needed to control the lights over BLE, though several features remain unexplored. Contributions are welcome. A demo code implementation for the ESP32 is provided for controlling the lights over BLE using the documented payloads.
