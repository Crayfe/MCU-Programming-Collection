//Código para prototipo de sensor de temperatura y humedad
#include "DHT.h"
/*Cosideraciones importantes
 * 
Pin   Función
1       Vcc     3-5V
2       Datos   Considerar poner una resistencia pull-up de 10k
3       ---
4       Gnd

Velocidad de lectura máxima: 0.5Hz (2 segundos por muestra)
*/
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
  humedad = dht.readHumidity();
  temperatura = dht.readTemperature();
  //Verificamos datos válidos
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.print("Fallo de lectura del sensor DHT");
    Serial.println(DHTTYPE);
    delay(2000);
    return;
  }
  Serial.print("Humedad: ");
  Serial.print(humedad);
  Serial.print("% Temperatura: ");
  Serial.print(temperatura);
  Serial.println("ºC");
  delay(2000);        //Esperamos 2 segundos
}
