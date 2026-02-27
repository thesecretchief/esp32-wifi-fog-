#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

int intensity = 2; // 1 = gentle, 2 = medium (default), 3 = aggressive

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! 🌫️ WiFi Fog Machine active");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Random choice of fast targets for realistic traffic
    const char* urls[] = {
      "http://1.1.1.1",
      "https://www.cloudflare.com/cdn-cgi/trace",
      "http://connectivitycheck.gstatic.com/generate_204"
    };
    
    if (random(100) < 70) {  // 70% chance per cycle
      http.begin(urls[random(0, 3)]);
      http.setUserAgent("ESP32-WiFiFog/1.0");
      http.GET();
      http.end();
    }
    
    // Variable delay based on intensity (more random = harder to filter)
    int baseDelay = (intensity == 1) ? 600 : (intensity == 2) ? 350 : 120;
    delay(baseDelay + random(80, 420));
  }
}
