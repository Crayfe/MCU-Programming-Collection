/*
 * Código para probar el funcionamiento de un sensor de colores TCS34725 con el lenguaje de Arduino.
 * El mismo código funciona para ESP32

 
 * 
 */
#include <Wire.h>

#define tcsAddr 0x29    //Dirección I2C del TCS34725
//Direcciones de memoria
#define ENABLE           0x00    /* Power on - Writing 1 activates the internal oscillator, 0 disables it */
#define ATIME            0x01    /* Integration time */
#define CONTROL          0x0F    /* Set the gain level for the sensor */
#define CDATAL           0x14    /* Clear channel data */
#define CDATAH           0x15
#define RDATAL           0x16    /* Red channel data */
#define RDATAH           0x17
#define GDATAL           0x18    /* Green channel data */
#define GDATAH           0x19
#define BDATAL           0x1A    /* Blue channel data */
#define BDATAH           0x1B

//Options
#define ENABLE_PON       0x01    /* Power on - Writing 1 activates the internal oscillator, 0 disables it */
#define ENABLE_AEN       0x02   /* RGBC Enable - Writing 1 actives the ADC, 0 disables it */
#define INTEGRATIONTIME_700MS   0x00
#define GAIN_1X          0x00   /**<  No gain  */
#define GAIN_60X         0x03   /**<  No gain  */
#define CMD_Read_Word    0x20     /* RGBC Interrupt flag clear */


uint16_t red, green, blue, clearance;
//uint8_t H_red, H_green, H_blue;
//uint8_t L_red, L_green, L_blue;

void setup(void){
  Serial.begin(115200);
  Wire.begin();
    //TSC34725 init
  Wire.beginTransmission(tcsAddr);
  Wire.write(ENABLE | 0x80);
  Wire.write(ENABLE_PON);
  Wire.endTransmission();
  delay(3)
  Wire.beginTransmission(tcsAddr);
  Wire.write(ENABLE | 0x80);
  Wire.write(ENABLE_PON | ENABLE_AEN);
  Wire.endTransmission();
  
  //TSC34725 Set integration time
  Wire.beginTransmission(tcsAddr);
  Wire.write(ATIME | 0x80);
  Wire.write(INTEGRATIONTIME_700MS);
  Wire.endTransmission();
  
  //TSC34725 Set gain
  Wire.beginTransmission(tcsAddr);
  Wire.write(CONTROL | 0x80);
  Wire.write(GAIN_1X  & 0xFF);
  Wire.endTransmission();
  

}
void loop(){
  //Leemos clear
  Wire.beginTransmission(tcsAddr);
  Wire.write(CDATAL | 0x80);               //Nos situamos en la dirección donde se empiezan a leer los colores               
  Wire.endTransmission();
  Wire.requestFrom(tcsAddr,2);      
  while(Wire.available() < 2);      
  clearance =  (Wire.read() << 8) | (Wire.read() & 0xFF);

  //leemos red
  Wire.beginTransmission(tcsAddr);
  Wire.write(RDATAL | 0x80);               //Nos situamos en la dirección donde se empiezan a leer los colores               
  Wire.endTransmission();
  Wire.requestFrom(tcsAddr,2);      
  while(Wire.available() < 2);      
  red =  (Wire.read() << 8) | (Wire.read() & 0xFF);

  //leemos green
   Wire.beginTransmission(tcsAddr);
  Wire.write(GDATAL | 0x80);               //Nos situamos en la dirección donde se empiezan a leer los colores               
  Wire.endTransmission();
  Wire.requestFrom(tcsAddr,2);      
  while(Wire.available() < 2);      
  green = (Wire.read() << 8) | (Wire.read() & 0xFF);
  
  //leemos blue
  Wire.beginTransmission(tcsAddr);
  Wire.write(BDATAL | 0x80);               //Nos situamos en la dirección donde se empiezan a leer los colores               
  Wire.endTransmission();
  Wire.requestFrom(tcsAddr,2);      
  while(Wire.available() < 2);      
  blue =  (Wire.read() << 8) | (Wire.read() & 0xFF);
  

  Serial.println("Colors:");
  Serial.print("Red: ");
  Serial.println(red);
  Serial.print("Green: ");
  Serial.println(green);
  Serial.print("Blue: ");
  Serial.println(blue);
  Serial.print("Clearance: ");
  Serial.println(clearance);
/*
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
*/
  delay(2000);
  
}
