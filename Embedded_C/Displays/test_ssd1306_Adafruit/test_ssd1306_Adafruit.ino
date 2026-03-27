/*
 * Es necesario tener instaladas las librerías Adafruit_GFX y Adafruit_SSD1306 para que el programa funcione
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // El ancho del display en pixeles
#define SCREEN_HEIGHT 64 // El alto del display en pixeles
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C // La dirección i2c del display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();  //Borramos el splash screen de Adafruit
  display.display();
}

void loop(){
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }
  display.display();
  delay(2000);
  
  display.clearDisplay();
  display.setTextSize(1);// Normal 1:1 pixeL
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Hello, world!"));
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.println(3.141592);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println("CRAYFE");
  display.display();
  delay(2000);
}
