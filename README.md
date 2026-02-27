# esp32-wifi-fog

**Make your WiFi "blind" to movement.**

Turn a cheap ESP32 board into a privacy guardian that continuously injects realistic dummy traffic onto your home WiFi network. By flooding the channel with pings, fake web requests, and background packets, it adds noise to the Channel State Information (CSI) and Beamforming Feedback Information (BFI) that WiFi routers use to create "radio images" of people — even through walls.

This is the perfect **defensive companion** to the [WiFi Can See You — Weekend Project](https://foropoulosnow.com/blog/posts/wifi-can-see-you-weekend-project.html).

### Why it works
Modern WiFi can detect and track human movement using nothing but radio wave reflections. esp32-wifi-fog makes those reflections noisy and unreliable without breaking your internet speed or requiring router changes.

### Features
- Extremely low power (~0.5 W) — runs 24/7 on USB
- Adjustable noise intensity: Gentle / Medium / Aggressive
- Generates realistic traffic patterns (pings, HTTP requests, UDP, etc.)
- Works with **any** existing router (no configuration needed)
- ESPHome version for one-click Home Assistant integration
- Supports ESP32-S3, ESP32-C6, ESP32-C3 and most other variants
- 100% local, open-source, no cloud, no tracking

### Project Structure

```
esp32-wifi-fog-/
├── CLAUDE.md              # Project context for AI sessions
├── README.md              # This file
├── LICENSE                # MIT
├── arduino/
│   ├── wifi_fog.ino       # Main Arduino sketch
│   └── config.h           # User configuration (WiFi, intensity, etc.)
├── esphome/
│   └── wifi_fog.yaml      # ESPHome configuration
└── platformio.ini         # PlatformIO build config
```

### Installation

#### Hardware Needed (total cost ~$7-12)
- Any ESP32 board (ESP32-S3, ESP32-C6, or ESP32-C3 recommended — best WiFi performance)
- USB cable for flashing + power (any 5V USB charger works for 24/7 use)
- Optional: small 3D-printed case or just leave it plugged in near your router

#### Option 1: ESPHome (Recommended — easiest, perfect for Home Assistant users)

1. Open ESPHome in Home Assistant (or the standalone ESPHome dashboard).
2. Click **+ New Device** → give it name `wifi-fog` → choose your ESP32 board.
3. Replace the entire generated YAML with the contents of [`esphome/wifi_fog.yaml`](esphome/wifi_fog.yaml).
4. Click **Install** → plug in your ESP32 (hold BOOT button if it asks).
5. Plug the board near your main router and watch the fog begin!

#### Option 2: Arduino IDE

1. Open `arduino/wifi_fog.ino` in Arduino IDE.
2. Edit `arduino/config.h` with your WiFi credentials and preferred intensity level.
3. Select your ESP32 board under **Tools → Board**.
4. Click **Upload**.

#### Option 3: PlatformIO

1. Edit `arduino/config.h` with your WiFi credentials and preferred intensity level.
2. Build and upload:
   ```bash
   # For standard ESP32
   pio run -e esp32 -t upload

   # For ESP32-S3
   pio run -e esp32s3 -t upload

   # For ESP32-C3
   pio run -e esp32c3 -t upload
   ```

### Configuration

All settings live in [`arduino/config.h`](arduino/config.h):

| Setting | Default | Description |
|---------|---------|-------------|
| `WIFI_SSID` | `YOUR_WIFI_SSID` | Your WiFi network name |
| `WIFI_PASSWORD` | `YOUR_WIFI_PASSWORD` | Your WiFi password |
| `INTENSITY_LEVEL` | `2` | 1=Gentle, 2=Medium, 3=Aggressive |
| `REQUEST_PROBABILITY` | `70` | Percent chance of request per cycle |
| `HTTP_TIMEOUT_MS` | `2000` | HTTP request timeout |
| `STATUS_INTERVAL_MS` | `60000` | Serial status print interval |

### Quick Start
1. Flash the firmware (ESPHome or Arduino)
2. Plug it in near your router
3. Walk around and watch your motion detector go from clear to blurry

Perfect for anyone who built the ESPectre-style WiFi motion detector and now wants the privacy version.

**Cost:** ~$7-12
**Time to build:** < 15 minutes
**License:** MIT

---

Built as an ethical, defensive tool for your own home network only.
Your house. Your rules. Your fog.
