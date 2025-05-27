/*    codigo para obtener la fecha y hora de un servidor NTP con ESP32
 *    NTP significa Netwotk Time Protocol. Es un protocolo de de internet estandar para sincronizar relojes
 */
#include <WiFi.h>
#include "time.h"

const char* ssid       = "tu_ssid";
const char* password   = "tu_pass";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;       // Zona horaria
const int   daylightOffset_sec = 3600;  // Horario de verano si aplica

struct tm timeinfo;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s", ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("CONNECTED!");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  // Esperar a que el ESP32 sincronice la hora con NTP
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void loop()
{
  delay(1000);  // Esperar 1 segundo antes de la siguiente comprobación
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  else
  {
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  }
}
