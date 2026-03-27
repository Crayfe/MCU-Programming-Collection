#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define DS1307_ADDR 0x68
#define OLED_ADDR 0x3C


Adafruit_SSD1306 display(-1);
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

void setup() {

  second = 00;
  minute = 57;
  hour = 11;
  dayOfWeek = 7;
  dayOfMonth = 1;
  month = 4;
  year = 18;
  
  Serial.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {

  Serial.print("Reading date from DS1307...");
  display.clearDisplay();
  DS1307_get_date(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  display.setCursor(0,0);
  print_date();
  display.display();
}
byte dec_to_BCD(byte dec){
  return ( (dec/10*16) + (dec%10) );
}
byte BCD_to_dec(byte bcd){
  return ( (bcd/16*10) + (bcd%16) );
}
void DS1307_get_date(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
  Wire.beginTransmission(DS1307_ADDR);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDR, 7);
  *second     = BCD_to_dec(Wire.read() & 0x7f);
  *minute     = BCD_to_dec(Wire.read());
  *hour       = BCD_to_dec(Wire.read() & 0x3f);
  *dayOfWeek  = BCD_to_dec(Wire.read());
  *dayOfMonth = BCD_to_dec(Wire.read());
  *month      = BCD_to_dec(Wire.read());
  *year       = BCD_to_dec(Wire.read());
}
void DS1307_set_date(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year){
   Wire.beginTransmission(DS1307_ADDR); // direccion 0x68 del ds1307
   Wire.write(0);
   Wire.write(dec_to_BCD(second));
   Wire.write(dec_to_BCD(minute));
   Wire.write(dec_to_BCD(hour));
   Wire.write(dec_to_BCD(dayOfWeek));
   Wire.write(dec_to_BCD(dayOfMonth));
   Wire.write(dec_to_BCD(month));
   Wire.write(dec_to_BCD(year));
   Wire.endTransmission();
}
void print_date(){
  display.setTextSize(2);
  if (hour < 10) display.print("0");
  display.print(hour, DEC);
  display.print(":");  
  if (minute < 10) display.print("0");
  display.print(minute, DEC);
  display.print(":");
  if (second < 10) display.print("0");
  display.println(second, DEC);  
  display.setTextSize(2);
  if (dayOfMonth < 10) display.print("0");
  display.print(dayOfMonth, DEC); 
  display.print("/");
  if (month < 10) display.print("0");
  display.print(month, DEC);  
  display.print("/");   
  display.print("20");
  if (year < 10) display.print("0");
  display.println(year, DEC);
    display.setTextSize(3);
  switch (dayOfWeek){
    case 1:
      display.println("Monday");
      break;
    case 2:
      display.println("Tuesday");
      break;
    case 3:
      display.println("Wednesday");
      break;
    case 4:
      display.println("Thursday");
      break;
    case 5:
      display.println("Friday");
      break;
    case 6:
      display.println("Saturday");
      break;
    case 7:
      display.println("Sunday");
      break;
   }
  
}

