#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

unsigned long lastStatusTime = 0;
unsigned long requestCount = 0;
unsigned long failCount = 0;

void printMacAddress() {
  Serial.println("============================================");
  Serial.println("  ESP32 WiFi Fog Machine");
  Serial.println("============================================");

  // Print MAC address prominently - this is the key for filtering.
  // Your own CSI/BFI motion detection can exclude this MAC to see
  // through the fog, while external observers cannot.
  Serial.print("  MAC address: ");
  Serial.println(WiFi.macAddress());
  Serial.println();
  Serial.println("  Save this MAC address! Add it to your CSI");
  Serial.println("  capture filter to exclude fog traffic from");
  Serial.println("  your own motion detection analysis.");
  Serial.println("============================================");
}

void printConfig() {
  Serial.print("Intensity: ");
  Serial.print(INTENSITY_LEVEL);
  Serial.print(" | Base delay: ");
  Serial.print(BASE_DELAY_MS);
  Serial.print("ms | Probability: ");
  Serial.print(REQUEST_PROBABILITY);
  Serial.print("% | Targets: ");
  Serial.println(NUM_TARGETS);
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");

  printMacAddress();
  printConfig();

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Fog active. External observers see noise;");
  Serial.println("filter the MAC above in your own CSI tools.");
  Serial.println();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (random(100) < REQUEST_PROBABILITY) {
      HTTPClient http;
      const char* url = TARGETS[random(0, NUM_TARGETS)];

      http.setTimeout(HTTP_TIMEOUT_MS);
      http.setReuse(false);
      http.begin(url);
      http.setUserAgent("ESP32-WiFiFog/1.0");
      int httpCode = http.GET();
      http.end();

      if (httpCode > 0) {
        requestCount++;
      } else {
        failCount++;
      }
    }

    // Periodic status output
    unsigned long now = millis();
    if (now - lastStatusTime >= STATUS_INTERVAL_MS) {
      Serial.print("[fog] uptime=");
      Serial.print(now / 1000);
      Serial.print("s ok=");
      Serial.print(requestCount);
      Serial.print(" fail=");
      Serial.print(failCount);
      Serial.print(" mac=");
      Serial.println(WiFi.macAddress());
      lastStatusTime = now;
    }

    // Variable delay: base + random jitter (harder to fingerprint)
    delay(BASE_DELAY_MS + random(RANDOM_DELAY_MIN, RANDOM_DELAY_MAX));
  } else {
    Serial.println("[fog] WiFi disconnected, reconnecting...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(5000);
  }
}
