# display-face-on-128x64-oled-with-arduino
# Face Display Project

This Arduino project uses an OLED display and a button to cycle through different face graphics. It is built using the Adafruit GFX and SSD1306 libraries.

## Description

The project displays different faces on a 128x64 OLED screen. A button is used to cycle through these faces. The program also includes functionality for eye animations and button press detection, with plans for further enhancements.

## Components

- Arduino board
- 128x64 OLED display (SSD1306)
- Push button
- Wires and breadboard

## Wiring

- **A4** > OLED SDA
- **A5** > OLED SCL
- **5V** > Button IN, OLED VCC
- **GND** > OLED GND, Button OUT
- **D8** > Button IN
- **D9** > OLED RESET
- **LED_BUILTIN** for visual feedback on button press

## Libraries

Include the following libraries in your Arduino IDE:

- `Adafruit_GFX.h`
- `Adafruit_SSD1306.h`
- `Wire.h`

## Setup

1. **Initialize Serial Communication:**
   ```cpp
   Serial.begin(9600);
   while (!Serial) {
     ; // Wait for serial port to connect. Needed for native USB port only
   }
