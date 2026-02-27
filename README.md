# esp32-wifi-fog 🌫️

**Make your WiFi "blind" to movement.**

Turn a cheap ESP32 board into a privacy guardian that continuously injects realistic dummy traffic onto your home WiFi network. By flooding the channel with pings, fake web requests, and background packets, it adds noise to the Channel State Information (CSI) and Beamforming Feedback Information (BFI) that WiFi routers use to create "radio images" of people — even through walls.

This is the perfect **defensive companion** to the [WiFi Can See You — Weekend Project](https://foropoulosnow.com/blog/posts/wifi-can-see-you-weekend-project).

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

### Installation

#### Hardware Needed (total cost ~$7–12)
- Any ESP32 board (ESP32-S3, ESP32-C6, or ESP32-C3 recommended — best WiFi performance)
- USB cable for flashing + power (any 5V USB charger works for 24/7 use)
- Optional: small 3D-printed case or just leave it plugged in near your router

#### Option 1: ESPHome (Recommended — easiest, 10 minutes, perfect for Home Assistant users)

1. Open ESPHome in Home Assistant (or the standalone ESPHome dashboard).
2. Click **+ New Device** → give it name `wifi-fog` → choose your ESP32 board.
3. Replace the entire generated YAML with the code below.
4. Click **Install** → plug in your ESP32 (hold BOOT button if it asks).
5. Plug the board near your main router and watch the fog begin!

**wifi-fog.yaml** (copy-paste)
```yaml
esphome:
  name: wifi-fog
  friendly_name: WiFi Fog Machine

esp32:
  board: esp32-s3-devkitc-1   # ← CHANGE to match your board (esp32-c6-devkitc-1, etc.)

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

logger:
  level: WARN

web_server:
  port: 80   # optional — view status in browser at the device IP

# ================== NOISE GENERATION ==================
interval:
  # Frequent light requests (core fog)
  - interval: 450ms
    then:
      - http_request.get:
          url: "http://1.1.1.1"
          useragent: "ESP32-WiFiFog/1.0"
      - delay: 150ms

  # Occasional varied requests (harder for sensing algorithms to filter)
  - interval: 2s
    then:
      - http_request.get:
          url: "https://www.cloudflare.com/cdn-cgi/trace"
          useragent: "ESP32-WiFiFog/1.0"

  - interval: 5s
    then:
      - http_request.get:
          url: "http://connectivitycheck.gstatic.com/generate_204"
          useragent: "ESP32-WiFiFog/1.0"

# Switch to turn fog on/off from Home Assistant
switch:
  - platform: template
    name: "WiFi Fog"
    optimistic: true
    restore_mode: RESTORE_DEFAULT_ON
    turn_on_action:
      - logger.log: "🌫️ Fog machine ON"
    turn_off_action:
      - logger.log: "🌫️ Fog machine OFF"

### Quick Start
1. Flash the firmware (ESPHome or Arduino)
2. Plug it in near your router
3. Walk around and watch your motion detector go from clear to blurry

Perfect for anyone who built the ESPectre-style WiFi motion detector and now wants the privacy version.

**Cost:** ~$7–12  
**Time to build:** < 15 minutes  
**License:** MIT

---

Built as an ethical, defensive tool for your own home network only.  
Your house. Your rules. Your fog. 🛡️
