#include <Wire.h>
#define DS1307_ADDR 0x68

byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  second = 00;
  minute = 35;
  hour = 21;
  dayOfWeek = 6;
  dayOfMonth = 23;
  month = 11;
  year = 19;
  
}
void loop() {
  Serial.println("DS1307 options:");
  Serial.println("1) Read date from DS1307");
  Serial.println("2) Write date into DS1307");
  Serial.println("3) load new date");
  Serial.println("4) show new date");
  while(Serial.available()==0);
  char c = Serial.read();
  if(c=='1'){
    Serial.print("Reading date from DS1307...");
    DS1307_get_date(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    print_date();
  }
  else if(c=='2'){
    Serial.print("Writing date from DS1307...");
    DS1307_set_date(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
  }
  else if(c=='3'){
    Serial.print("Loading date...");
    
  }
  else if(c=='4'){
    print_date();
  }
  else{
    
  }

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
  if (dayOfMonth < 10) Serial.print("0");
  Serial.print(dayOfMonth, DEC); 
  Serial.print("/");
  if (month < 10) Serial.print("0");
  Serial.print(month, DEC);  
  Serial.print("/");   
  Serial.print("20");
  if (year < 10) Serial.print("0");
  Serial.print(year, DEC);
  Serial.print("  ");
  if (hour < 10) Serial.print("0");
  Serial.print(hour, DEC);
  Serial.print(":");  
  if (minute < 10) Serial.print("0");
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10) Serial.print("0");
  Serial.print(second, DEC);  
  Serial.print("  Day:");
  switch (dayOfWeek){
    case 1:
      Serial.println(" Monday");
      break;
    case 2:
      Serial.println(" Tuesday");
      break;
    case 3:
      Serial.println(" Wednesday");
      break;
    case 4:
      Serial.println(" Thursday");
      break;
    case 5:
      Serial.println(" Friday");
      break;
    case 6:
      Serial.println(" Saturday");
      break;
    case 7:
      Serial.println(" Sunday");
      break;
   }
}
