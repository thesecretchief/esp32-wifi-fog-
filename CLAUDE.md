# ESP32 WiFi Fog - Project Context

## Purpose
Privacy tool that generates random WiFi traffic to confuse BFI/CSI motion sensing.
WiFi routers can detect human movement through beamforming feedback data. This tool
injects noise to degrade that sensing capability.

## Architecture
- **Arduino version**: `arduino/wifi_fog.ino` + `arduino/config.h`
- **ESPHome version**: `esphome/wifi_fog.yaml`

## Configuration (config.h)
All user-configurable values are in `arduino/config.h`:
- WiFi credentials
- Intensity level (1=gentle, 2=medium, 3=aggressive)
- Target URLs for HTTP requests
- Timing parameters (min/max delays)
- Request probability

## Build
- Arduino IDE: Open `arduino/wifi_fog.ino`, select ESP32 board, upload
- PlatformIO: `pio run -t upload`
- ESPHome: `esphome run esphome/wifi_fog.yaml`

## Related Content
- Blog post: https://foropoulosnow.com/blog/posts/wifi-privacy-defense-cheap-countermeasures.html
- Part 1: https://foropoulosnow.com/blog/posts/wifi-can-see-you-weekend-project.html

## Code Standards
- All magic numbers should be constants in config.h
- Serial output at 115200 baud for debugging
- Use HTTPClient for requests (built into ESP32 Arduino core)
