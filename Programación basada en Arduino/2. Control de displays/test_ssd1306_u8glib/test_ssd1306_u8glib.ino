#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
/*
Ejemplo completo: https://github.com/BasOnTech/Arduino-Beginners-NL/blob/master/E18-OLED-I2C-SSD1306-128X64/OLED-I2C-SSD1306-128X64.ino
*/

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_box_title(uint8_t a) {
  u8g2.drawStr( 10+a*2, 5, "u8g2 lib Test");
  u8g2.drawStr( 10, 20, "Hello, Crayfe!");
  
  u8g2.drawFrame(0,0,u8g2.getDisplayWidth(),u8g2.getDisplayHeight() );
}

uint8_t draw_state = 0;

void draw(void) {
  u8g2_prepare();
  switch(draw_state >> 3) {
    case 0: u8g2_box_title(draw_state&7); break;
  }
}

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  
  // increase the state
  draw_state++;
  if ( draw_state >= 0 )
    draw_state = 0;

  // delay between each page
  delay(150);
}
