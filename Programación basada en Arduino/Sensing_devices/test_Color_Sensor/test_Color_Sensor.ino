/*
 * Código para probar el funcionamiento de un sensor de colores TCS34725 con el lenguaje de Arduino.
 * El mismo código funciona para ESP32

 
 * 
 */
#include <Wire.h>

#define tcsAddr 0x29    //Dirección I2C del TCS34725
#define colors 0x14    //Dirección de memoria donde se leen los colores
#define reset 0x00


int8_t H_red, H_green, H_blue;
int8_t L_red, L_green, L_blue;

void setup(void){
  Serial.begin();
  Wire.begin();
  
  //Reset del sensor de colores
  Wire.beginTransmission(tcsAddr);
  Wire.write(reset);
  Wire.write(0x00);
  Wire.endTransmission();

  //Configuración adicional
  
  
  
  
  
  
}
void loop(){
  //Leemos los registros donde se almacenan los colores
  Wire.beginTransmission(tcsAddr);
  Wire.write(colors);               //Nos situamos en la dirección donde se empiezan a leer los colores               
  Wire.endTransmission();
  
  Wire.requestFrom(tcsAddr,6);      //Petición de 6 bytes empezando por la dirección a la que apunta accXYZ
  while(Wire.available() < 6);      //Esperamos hasta leer 6 bytes del MPU6050
  //Aclaración: Wire.read() lee bloques de 1 byte. Por tanto para leer 16bits leemos 2 bytes consecutivos
  //para concatenarlos primero hacemos una lectura, después desplacamos el registro 8 bits y añadimos una segunda lectura con la operación "or" 
  H_red = Wire.read();
  L_red = Wire.read(); 
  H_green = Wire.read();
  L_green = Wire.read();
  H_blue = Wire.read();
  L_green = Wire.read();


  Serial.println("Colors:");
  Serial.print("Red: ");
  Serial.println(H_red);
  Serial.print("Green: ");
  Serial.println(H_green);
  Serial.print("Blue: ");
  Serial.println(H_blue);

  delay(2000);
  
}
