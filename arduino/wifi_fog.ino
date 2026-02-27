#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

unsigned long lastStatusTime = 0;
unsigned long requestCount = 0;

void setup() {
  Serial.begin(SERIAL_BAUD);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! WiFi Fog Machine active");
  Serial.print("Intensity level: ");
  Serial.println(INTENSITY_LEVEL);
  Serial.print("Base delay: ");
  Serial.print(BASE_DELAY_MS);
  Serial.println("ms");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (random(100) < REQUEST_PROBABILITY) {
      HTTPClient http;
      const char* url = TARGETS[random(0, NUM_TARGETS)];

      http.setTimeout(HTTP_TIMEOUT_MS);
      http.begin(url);
      http.setUserAgent("ESP32-WiFiFog/1.0");
      int httpCode = http.GET();
      http.end();

      requestCount++;
    }

    // Periodic status output
    unsigned long now = millis();
    if (now - lastStatusTime >= STATUS_INTERVAL_MS) {
      Serial.print("[fog] uptime=");
      Serial.print(now / 1000);
      Serial.print("s requests=");
      Serial.println(requestCount);
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
