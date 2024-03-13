/*
 * Control de servos con esp32, la librería Servo.h no es compatible
 */
#include <ESP32Servo.h>

Servo servo;
void setup() {
  servo.attach(4);

}

void loop() {
  servo.write(0);
  delay(2000);
  servo.write(90);
  delay(2000);
  servo.write(180);
  delay(2000);

  for(int i = 0; i < 180; i++){
    servo.write(i);
    delay(100);
  }
  for(int i = 0; i < 180; i++){
    servo.write(180-i);
    delay(100);
  }

}
