# ESP32 E-Ink Weather Display
This project plans to create a long lasting, battery powered weather display, with a rechargeable cell and custom PCB.

# Table of Contents
- [ESP32 E-Ink Weather Display](#esp32-e-ink-weather-display)
- [Table of Contents](#table-of-contents)
  - [Project Aims](#project-aims)
  - [Components Used (so far)](#components-used-so-far)
  - [Testing Arduino Display Code](#testing-arduino-display-code)
  - [Porting Arduino Code to ESP-IDF](#porting-arduino-code-to-esp-idf)

## Project Aims
* [x] Test E-Ink display is working with teh ESP32.
* [ ] Port Arduino E-Ink demo to ESP-IDF.
* [ ] Connect to WiFi.
* [ ] Get weather data from API.
* [ ] Display weather information.
* [ ] Deep sleep and waker every 30 minutes or on button press.
* [ ] Setup NVS for saving settings.
* [ ] Rechargeable battery circuitry (PMIC).
  * [ ] Battery Protection (under and over charge).
  * [ ] Hybrid power system - when the battery is being recharged, the PCB is still powered, but now from the non-battery source.
* [ ] Custom PCB bringing all this together.
* [ ] Make app that can connect to ESP (WiFi or BLE?).

## Components Used (so far)
- ESP32-S3 Dev Kit.
- Waveshare E-Paper Driver HAT Rev2.3.
- 7.5inch e-Paper display.

## Testing Arduino Display Code

Example code taken from [here](https://www.waveshare.com/wiki/E-Paper_ESP32_Driver_Board#Demo_Code) on the WaveShare website.

To get an example building in Arduino IDE. I had to move the `\src` files into the example, in my case the `\epd7in5_V2-demo`.

I also changed the pin defines in the `DEV_Config.h` file to these as they are broken out on my board:
```
/**
 * GPIO config
**/
#define EPD_BUSY_PIN 35
#define EPD_RST_PIN  36
#define EPD_DC_PIN   37
#define EPD_CS_PIN   38
#define EPD_SCK_PIN  39
#define EPD_MOSI_PIN 40
```

## Porting Arduino Code to ESP-IDF

- VSCode ESP-IDF Extension 1.9.0.
- ESP-IDF 5.3.2.

