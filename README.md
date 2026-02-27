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
