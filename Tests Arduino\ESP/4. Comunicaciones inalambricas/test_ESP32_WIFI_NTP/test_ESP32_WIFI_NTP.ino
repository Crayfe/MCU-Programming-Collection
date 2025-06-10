/*    codigo para obtener la fecha y hora de un servidor NTP con ESP32
 *    NTP significa Netwotk Time Protocol. Es un protocolo de de internet estandar para sincronizar relojes
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "time.h"

#define SCREEN_WIDTH 128 // El ancho del display en pixeles
#define SCREEN_HEIGHT 64 // El alto del display en pixeles
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C // La dirección i2c del display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid       = "vodafoneD94D";
const char* password   = "K7UXJ3HU28XM82";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;       // Zona horaria
const int   daylightOffset_sec = 3600;  // Horario de verano si aplica

struct tm timeinfo;

// Control bomba
const int bombaPin = 17;
const int intervaloDias = 3;     // Cada 3 días
const int horaRiego = 12;        // A las 12:00 del mediodía
const int duracionRiegoSeg = 25; // Segundos que se activa

unsigned long tiempoInicioRiego = 0;
bool bombaEncendida = false;
int ultimoDiaActivado = -1;  // Para evitar repetir el mismo día

void setup() {
  pinMode(bombaPin, OUTPUT);
  digitalWrite(bombaPin, LOW); // Apagada inicialmente

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.display();

  WiFi.begin(ssid, password);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Connecting to ");
  display.println(ssid);
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }

  display.clearDisplay();
  display.println("CONNECTED!");
  display.display();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if (!getLocalTime(&timeinfo)) {
    display.clearDisplay();
    display.println("Failed to obtain time");
    display.display();
    return;
  }

  display.clearDisplay();
  display.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  display.display();
}

void loop() {
  display.setCursor(0,0);
  if (!getLocalTime(&timeinfo)) {
    display.clearDisplay();
    display.println("Failed to obtain time");
    display.display();
    delay(1000);
    return;
  }

  display.clearDisplay();
  display.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  int diaDelAnio = timeinfo.tm_yday;
  int horaActual = timeinfo.tm_hour;

  // Si es día de riego y son las 12:00 y no se ha activado hoy
  if ((diaDelAnio % intervaloDias == 0) &&
      horaActual == horaRiego &&
      diaDelAnio != ultimoDiaActivado) {

    digitalWrite(bombaPin, HIGH);
    bombaEncendida = true;
    tiempoInicioRiego = millis();
    ultimoDiaActivado = diaDelAnio;

    display.println("RIEGO ACTIVADO");
  }

  // Apagar la bomba si ha pasado el tiempo
  if (bombaEncendida && (millis() - tiempoInicioRiego > duracionRiegoSeg * 1000)) {
    digitalWrite(bombaPin, LOW);
    bombaEncendida = false;
    display.println("RIEGO FINALIZADO");
  }

  display.display();
  delay(1000);
}
