#include <ESP32Servo.h>

// Este código ha sido testado con un servo SG90
Servo myServo;
const int servoPin = 17;

// Se definen el mínimo y máximo ancho del pulso para el servo
const int minPulseWidth = 500; // 0.5 ms
const int maxPulseWidth = 2500; // 2.5 ms

void setup() {
  // Se enlaza el servo al pin especificado y se le asigna el rango ge pulsos
  myServo.attach(servoPin, minPulseWidth, maxPulseWidth);
  myServo.setPeriodHertz(50); // Standard 50Hz servo
}

void loop() {
  // Rota el servo de 0 a 180 grados
  for (int angle = 0; angle <= 180; angle++) {
    int pulseWidth = map(angle, 0, 180, minPulseWidth, maxPulseWidth);
    myServo.writeMicroseconds(pulseWidth);
    delay(10);
  }
  // Rota el servo de 180 a 0 grados más rápido
  for (int angle = 180; angle >= 0; angle--) {
    int pulseWidth = map(angle, 0, 180, minPulseWidth, maxPulseWidth);
    myServo.writeMicroseconds(pulseWidth);
    delay(5);
  }
}
