#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// WIFI CONFIGURATION
// ============================================
#define WIFI_SSID     "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// ============================================
// INTENSITY LEVELS
// 1 = Gentle (longer delays, less bandwidth)
// 2 = Medium (balanced)
// 3 = Aggressive (short delays, more noise)
// ============================================
#define INTENSITY_LEVEL 2

// ============================================
// TIMING (milliseconds)
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
#define HTTP_TIMEOUT_MS 2000

// ============================================
// TARGET ENDPOINTS
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
