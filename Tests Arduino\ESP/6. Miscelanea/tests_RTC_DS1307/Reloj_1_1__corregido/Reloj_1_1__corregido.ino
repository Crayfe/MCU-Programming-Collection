#include <Wire.h>
#include <SD.h>
File myFile;
boolean SDwritten = false;
#define DS1307_I2C_ADDRESS 0x68

int led0 = 9;
int led1 = 7;
const int chipSelect = 8;
const int analogInPin = A0;
int AN0 = 0;
byte dt0 = 00;
// Convierte números normales decimales a BCD (binario decimal codificado)
byte decToBcd(byte val){return ( (val/10*16) + (val%10) );}
// Convierte BCD (binario decimal codificado) a números normales decimales 
byte bcdToDec(byte val){return ( (val/16*10) + (val%16) );}
// Establece la fecha y el tiempo del ds1307
void getDateDs1307(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{ Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  // Alguno de estos necesitan enmascarar porque ciertos bits son bits de control	
  *second     = bcdToDec(Wire.read() & 0x7f);
  *minute     = bcdToDec(Wire.read());
  *hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  *dayOfWeek  = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month      = bcdToDec(Wire.read());
  *year       = bcdToDec(Wire.read());}

void setup()
{
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);  
  
  if(minute == dt0){
    pinMode(10, OUTPUT);
   if (!SD.begin(chipSelect)) {    
     digitalWrite(led1, HIGH);   
     delay(3000);              
     digitalWrite(led1, LOW);   
     return;
   }
   myFile = SD.open("log.txt", FILE_WRITE);
   if (myFile) {
     switch (dayOfWeek) 
	{
      case 1:
      myFile.print("  Lunes ");       break;
      case 2:
      myFile.print("  Martes ");      break;
      case 3:
      myFile.print("  Miercoles ");   break;
      case 4:
      myFile.print("  Jueves ");      break;
      case 5:
      myFile.print("  Viernes ");     break;
      case 6:
      myFile.print("  Sabado ");      break;
      case 7:
      myFile.print("  Domingo ");     break;
   }
   if (dayOfMonth < 10) myFile.print("0");
   myFile.print(dayOfMonth, DEC);
   myFile.print("/");
   if (month < 10) myFile.print("0");
   myFile.print(month, DEC);  
   myFile.print("/");   
   myFile.print("20");
   if (year < 10) myFile.print("0");
   myFile.print(year, DEC);
   myFile.print(" ");
   myFile.print("hora: ");  
   if (hour < 10) myFile.print("0");
   myFile.print(hour, DEC);
   myFile.print(":");  
   if (minute < 10) myFile.print("0");
   myFile.print(minute, DEC);
   myFile.print(":");
   if (second < 10) myFile.print("0");
   myFile.print(second, DEC);    
   myFile.print(" ");

   //Muestra tambien la temperatura acorde con la hora
   AN0 = analogRead(analogInPin);
   myFile.print(AN0 * 0.004882812 * 100 - 4.5 - 273.15);
   myFile.println(" C");
   myFile.close();
   }
 }
   while(minute == dt0){
     digitalWrite(led0, HIGH);   
     delay(1000);              
     digitalWrite(led0, LOW);   
     delay(1000);
     getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
   }
  }
