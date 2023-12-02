//Código para prototipo de sensor de temperatura y humedad
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
float humedad;
float temperatura;
void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  humedad = dht.readHumidity();
  temperatura = dht.readTemperature();
  //Verificamos datos válidos
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.print("Fallo de lectura del sensor DHT");
    Serial.println(DHTTYPE);
    return;
  }
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("% Temperatura: ");
  Serial.print(temperatura);
  Serial.println("ºC");
}
