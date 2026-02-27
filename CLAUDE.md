# ESP32 WiFi Fog - Project Context

## Purpose
Privacy tool that generates random WiFi traffic to confuse BFI/CSI motion sensing.
WiFi routers can detect human movement through beamforming feedback data. This tool
injects noise to degrade that sensing capability.

## Architecture
- **Arduino version**: `arduino/wifi_fog.ino` + `arduino/config.h`
- **ESPHome version**: `esphome/wifi_fog.yaml`

## Key Design: MAC-Based Dual Use
The fog is designed so the home user can run their own CSI/BFI motion detection
while blocking external observers:

- CSI/BFI data is tracked **per-device by MAC address**
- The fog device prints its MAC on boot and in periodic status lines
- The home user excludes the fog MAC in their CSI capture filter
- External observers don't know which device to filter, so the noise is effective

This means the fog device provides privacy protection against external sensing
while remaining transparent to the home user's own motion detection setup.

## Configuration (config.h)
All user-configurable values are in `arduino/config.h`:
- WiFi credentials
- Intensity level (1=gentle, 2=medium, 3=aggressive)
- Target URLs for HTTP requests
- Timing parameters (min/max delays)
- Request probability
- HTTP timeout

## Network Impact
Near-zero. At medium intensity: ~1.2 requests/sec, ~0.4 KB/s, ~1.2 MB/hour.
All targets are lightweight connectivity-check endpoints (HTTP 204, captive portal).
Less traffic than a single idle browser tab.

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
- MAC address must be printed on boot and in status lines
