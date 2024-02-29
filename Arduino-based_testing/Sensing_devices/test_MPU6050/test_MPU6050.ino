/*
 * Código para probar el funcionamiento de un acelerómetro y giroscopio MPU6050 con el lenguaje de Arduino.
 * El mismo código funciona para ESP32

 
 * 
 */
#include <Wire.h>

#define mpuAddr 0x68    //Dirección I2C del MPU6050
#define girConf 0x1B    //Dirección de memoria de la configuración del giroscopio
#define accConf 0x1C    //Dirección de memoria de la configuración del acelerómetro
#define accXYZ  0x3B    //Direccion de memoria donde se leen las acereraciones de los ejes xyz
#define girXYZ  0x43    //Direccion de memoria donde se leen los giros de los ejes xyz

int16_t accX, accY, accZ;  //variables de 16 bits donde almacenar las lecturas de aceleración
int16_t girX, girY, girZ;  //variables de 16 bits donde almacenar las lecturas de giro

void setup(void){
  Serial.begin(9600);
  Wire.begin();
  //SETUP MPU6050
  //El dispositivo MPU6050 tiene dos posibles interfaces I2C, por tanto tiene dos direcciones: b1101000 y b1101001, que en exadecimal son 
  // 0x68 y 0x69 respectivamente (utilizaremos la primera dirección
  Wire.beginTransmission(mpuAddr);  //Dirección I2C del MPU6050
  
  // Hacemos reset del dispositivo modificando el registro 0x6B (PWR_MGMT_1) poniéndo el registro a b0000000
  Wire.write(0x6B);                 //Dirección PWR_MGMT_1
  Wire.write(0x00);                 //Wire.write(0b00000000);
  Wire.endTransmission();           //después de cada petición finalizamos la transmisión

  // Para hacer la configuración del acelerómetro y del giroscopio tenemos los registros 0x1B y 0x1C respectivamente
  Wire.beginTransmission(mpuAddr);  //Dirección I2C del MPU6050
  Wire.write(girConf);              //Dirección de memoria de la configuración del giroscopio
  Wire.write(0x00);                 // +/- 250º/seg
  Wire.endTransmission(); 

  Wire.beginTransmission(mpuAddr); 
  Wire.write(accConf);              //Dirección de memoria de la configuración del acelerómetro
  Wire.write(0x00);                 // +/- 2g
  Wire.endTransmission(); 
  
}
void loop(){
  //leemos los registros del acelerómetro
  Wire.beginTransmission(mpuAddr); 
  Wire.write(accXYZ);               //Nos situamos en la dirección donde se empiezan a leer las aceleraciones                
  Wire.endTransmission();
  Wire.requestFrom(mpuAddr,6);      //Petición de 6 bytes empezando por la dirección a la que apunta accXYZ
  while(Wire.available() < 6);      //Esperamos hasta leer 6 bytes del MPU6050
  //Aclaración: Wire.read() lee bloques de 1 byte. Por tanto para leer 16bits leemos 2 bytes consecutivos
  //para concatenarlos primero hacemos una lectura, después desplacamos el registro 8 bits y añadimos una segunda lectura con la operación "or" 
  accX = Wire.read()<<8|Wire.read(); 
  accY = Wire.read()<<8|Wire.read(); 
  accZ = Wire.read()<<8|Wire.read(); 

  Wire.beginTransmission(mpuAddr); 
  Wire.write(girXYZ);               //Nos situamos en la dirección donde se empiezan a leer los giros               
  Wire.endTransmission();
  Wire.requestFrom(mpuAddr,6);      //Petición de 6 bytes empezando por la dirección a la que apunta girXYZ
  while(Wire.available() < 6);      //Esperamos hasta leer 6 bytes del MPU6050
  //Aclaración: Wire.read() lee bloques de 1 byte. Por tanto para leer 16bits leemos 2 bytes consecutivos
  //para concatenarlos primero hacemos una lectura, después desplacamos el registro 8 bits y añadimos una segunda lectura con la operación "or" 
  girX = Wire.read()<<8|Wire.read(); 
  girY = Wire.read()<<8|Wire.read(); 
  girZ = Wire.read()<<8|Wire.read(); 

  Serial.println("Acceleration:");
  Serial.print("X: ");
  Serial.println(((float)accX/16384.0));
  Serial.print("Y: ");
  Serial.println(((float)accY/16384.0));
  Serial.print("Z: ");
  Serial.println(((float)accZ/16384.0));

  Serial.println("Rotation:");
  Serial.print("X: ");
  Serial.println((girX/131.0));
  Serial.print("Y: ");
  Serial.println((girY/131.0));
  Serial.print("Z: ");
  Serial.println((girZ/131.0));
  delay(2000);
  

 
  
  
}
