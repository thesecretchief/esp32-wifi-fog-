# esp32-wifi-fog

**Make your WiFi "blind" to movement.**

Turn a cheap ESP32 board into a privacy guardian that continuously injects realistic dummy traffic onto your home WiFi network. By flooding the channel with pings, fake web requests, and background packets, it adds noise to the Channel State Information (CSI) and Beamforming Feedback Information (BFI) that WiFi routers use to create "radio images" of people — even through walls.

This is the perfect **defensive companion** to the [WiFi Can See You — Weekend Project](https://foropoulosnow.com/blog/posts/wifi-can-see-you-weekend-project.html).

### Why it works
Modern WiFi can detect and track human movement using nothing but radio wave reflections. esp32-wifi-fog makes those reflections noisy and unreliable without breaking your internet speed or requiring router changes.

### Features
- Extremely low power (~0.5 W) — runs 24/7 on USB
- Adjustable noise intensity: Gentle / Medium / Aggressive
- Generates realistic traffic patterns using lightweight connectivity-check endpoints
- Works with **any** existing router (no configuration needed)
- **Transparent to the home user** — filter by MAC address to see through the fog for your own motion detection
- ESPHome version for one-click Home Assistant integration
- Supports ESP32-S3, ESP32-C6, ESP32-C3 and most other variants
- Near-zero network impact (~0.4 KB/s at medium intensity)
- 100% local, open-source, no cloud, no tracking

### How it protects you (without slowing you down)

#### For external observers (neighbors, ISPs, anyone running CSI sensing against your network)
The fog device generates constant random WiFi traffic. Since CSI/BFI motion detection works by analyzing changes in radio wave reflections, the fog device's transmissions create additional multipath reflections that inject noise into any CSI capture. An external observer sees a jumble of signal changes and cannot reliably distinguish human movement from fog traffic — **unless** they know which device to filter out.

#### For you (the home user running your own motion detection)
CSI/BFI data is tracked **per-device by MAC address**. Since you control the fog device, you know its MAC address — it's printed to serial on every boot:

```
============================================
  ESP32 WiFi Fog Machine
============================================
  MAC address: A0:B1:C2:D3:E4:F5

  Save this MAC address! Add it to your CSI
  capture filter to exclude fog traffic from
  your own motion detection analysis.
============================================
```

In your CSI capture tool, exclude that MAC address. Your motion detection works perfectly while the fog remains impenetrable to anyone who doesn't know which device to filter.

#### Network impact
The fog generates almost no meaningful network load:

| Intensity | Requests/sec | Bandwidth | Per hour |
|-----------|-------------|-----------|----------|
| 1 (Gentle) | ~0.8 | ~0.2 KB/s | ~0.8 MB |
| 2 (Medium) | ~1.2 | ~0.4 KB/s | ~1.2 MB |
| 3 (Aggressive) | ~2.5 | ~0.8 KB/s | ~2.8 MB |

All targets are lightweight connectivity-check endpoints (HTTP 204 responses, captive portal checks) that return minimal data. The 1-second timeout prevents any single slow response from blocking the device. This is less traffic than a single browser tab generates in the background.

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
5. Open Serial Monitor (115200 baud) — note the MAC address printed on boot.

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
3. Open serial monitor: `pio device monitor` — note the MAC address printed on boot.

### Configuration

All settings live in [`arduino/config.h`](arduino/config.h):

| Setting | Default | Description |
|---------|---------|-------------|
| `WIFI_SSID` | `YOUR_WIFI_SSID` | Your WiFi network name |
| `WIFI_PASSWORD` | `YOUR_WIFI_PASSWORD` | Your WiFi password |
| `INTENSITY_LEVEL` | `2` | 1=Gentle, 2=Medium, 3=Aggressive |
| `REQUEST_PROBABILITY` | `70` | Percent chance of request per cycle |
| `HTTP_TIMEOUT_MS` | `1000` | HTTP request timeout (ms) |
| `STATUS_INTERVAL_MS` | `60000` | Serial status print interval (ms) |

### Using with your own motion detection

1. **Flash and boot** the fog device. Note the MAC address from serial output.
2. **In your CSI capture tool** (ESP32 CSI toolkit, Nexmon, etc.), add a MAC filter to exclude the fog device.
   - Example with ESP-CSI: filter out the fog MAC in your CSI callback
   - Example with Wireshark: `wlan.addr != A0:B1:C2:D3:E4:F5`
3. **Run your motion detection** as normal. The fog is invisible to your analysis but opaque to anyone else.

The fog device's MAC also appears in the periodic serial status line, so you can always find it:
```
[fog] uptime=3600s ok=2847 fail=3 mac=A0:B1:C2:D3:E4:F5
```

### Quick Start
1. Flash the firmware (ESPHome or Arduino)
2. Note the MAC address from serial output
3. Plug it in near your router
4. Exclude the MAC in your own CSI tools, or just let the fog run for pure defense

**Cost:** ~$7-12
**Time to build:** < 15 minutes
**License:** MIT

---

Built as an ethical, defensive tool for your own home network only.
Your house. Your rules. Your fog.
