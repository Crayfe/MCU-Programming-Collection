//test entrada analogica ESP8266
#include <ESP8266WiFi.h>
#define adc A0

void setup() {
Serial.begin(115200);

}
void loop() {
  int adcValue = map(analogRead(adc), 0, 340, 0, 1000);
    if(adcValue<900){
      if(adcValue<100){
        Serial.println(1);
      }else if(adcValue>350 && adcValue<450){
        Serial.println(2);
      }else if(adcValue>650 && adcValue<750){
        Serial.println(3);
      } 
    }
  delay(1000);
}
