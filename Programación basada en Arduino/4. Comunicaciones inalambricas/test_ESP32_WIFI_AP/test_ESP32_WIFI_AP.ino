#include <WiFi.h>

const char *ap_ssid = "CRAYFE-ESP32";
const char *ap_pass = "1234567890";

IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup() {
  
  Serial.begin(115200);
  Serial.print("CRAYFE-ESP32 CONF: ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  Serial.print("CRAYFE-ESP32 AP: ");
  Serial.println(WiFi.softAP(ap_ssid, ap_pass) ? "Ready" : "Failed!");
}

// the loop function runs over and over again forever
void loop() {

  Serial.print("[Server Connected] ");
  Serial.println(WiFi.softAPIP());

  delay(500);
}
