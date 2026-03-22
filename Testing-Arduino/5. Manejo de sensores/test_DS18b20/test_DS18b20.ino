//Prueba del sensor Dallas DS18b20
#include <OneWire.h>
#include <DallasTemperature.h>
#define DS18b20_pin 4

OneWire oneWire(DS18b20_pin);
DallasTemperature sensorDallas(&oneWire);
float Dallas_Temperature;

void setup() {
  Serial.begin(9200);
  sensorDallas.begin();       

}
void loop() {
  delay(2000);
  sensorDallas.requestTemperatures(); 
  Dallas_Temperature = sensorDallas.getTempCByIndex(0);
  Serial.print("Temperatura DS18b20: ");
  Serial.print(Dallas_Temperature); 

}
