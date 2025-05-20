/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DS1307_I2C_ADDRESS 0x68

// Declaraciones para SSD1306 display
#define SSD1306_I2C_ADDRESS 0x3C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Declaración de las variables a leer del RTC
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
  
}
void loop() {
  
  getDateDs1307(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  testscrolldate(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  
}

// Codifica números naturales decimales a BCD (binario decimal codificado)
byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}
// Decodifica BCD (binario decimal codificado) a números naturales decimales 
byte bcdToDec(byte val){
  return ( (val/16*10) + (val%16) );
}
// Establece la fecha y el tiempo del ds1307
void getDateDs1307(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
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
  *year       = bcdToDec(Wire.read());
 }

void testscrolldate(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year) {
  display.clearDisplay();

  display.setTextSize(4); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(5, 0);
  String month_ = String(*month);
  String day_ = String(*dayOfMonth);
  String year_ = String(*year);

  String hour_ = String(*hour);
  String minute_ = String(*minute);
  display.println(hour_+":"+minute_);
  display.setTextSize(1);
  display.println(day_+"/"+month_+"/"+year_);
   

  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}
