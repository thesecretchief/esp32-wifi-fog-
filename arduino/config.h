#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// WIFI CONFIGURATION
// ============================================
#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// ============================================
// INTENSITY LEVELS
// 1 = Gentle  ~0.8 req/s  ~0.2 KB/s  ~0.8 MB/hr
// 2 = Medium  ~1.2 req/s  ~0.4 KB/s  ~1.2 MB/hr
// 3 = Aggressive ~2.5 req/s ~0.8 KB/s ~2.8 MB/hr
// ============================================
#define INTENSITY_LEVEL 2

// ============================================
// TIMING (milliseconds)
// Cycle time = BASE_DELAY_MS + random(RANDOM_DELAY_MIN, RANDOM_DELAY_MAX)
// ============================================
#if INTENSITY_LEVEL == 1
  #define BASE_DELAY_MS 600
#elif INTENSITY_LEVEL == 2
  #define BASE_DELAY_MS 350
#else
  #define BASE_DELAY_MS 120
#endif

#define RANDOM_DELAY_MIN 80
#define RANDOM_DELAY_MAX 420

// ============================================
// REQUEST SETTINGS
// ============================================
#define REQUEST_PROBABILITY 70  // Percent chance per cycle (0-100)
#define HTTP_TIMEOUT_MS 1000    // 1s is plenty for connectivity endpoints

// ============================================
// TARGET ENDPOINTS
// These are lightweight connectivity-check URLs that return
// minimal data (0-204 bytes). They look like normal device
// traffic and put near-zero load on your internet connection.
// ============================================
const char* TARGETS[] = {
  "http://1.1.1.1/cdn-cgi/trace",
  "http://www.gstatic.com/generate_204",
  "http://connectivitycheck.android.com/generate_204",
  "http://captive.apple.com/hotspot-detect.html",
  "http://detectportal.firefox.com/success.txt"
};
const int NUM_TARGETS = sizeof(TARGETS) / sizeof(TARGETS[0]);

// ============================================
// DEBUG
// ============================================
#define SERIAL_BAUD 115200
#define STATUS_INTERVAL_MS 60000  // Print status every 60 seconds

#endif
