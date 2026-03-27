//hecho por Crayfe
//primero a declarar las variables a manejar
#include <Wire.h>
int estado = 0;  //variable que contiene el estado del boton +
int estado1 = 0; //variable que contola el estado del boton A
byte segundos = 0;
byte minutos = 0;
byte hora = 0;
byte diaSemana = 0;
byte diaMes = 0;
byte mes = 0;
byte anio = 0;
byte i2cAddress = 0x68;
byte W = 0;
byte W2 = 0;
void setup(){
 pinMode(9,INPUT);
 pinMode(8,INPUT);
 Serial.begin(9600);
 Wire.begin();
 Serial.println("Introduce valores");
}
void loop(){
   estado = digitalRead(9);   //lee las entradas A y +
   estado1 = digitalRead(8);

if (estado != estado1){  //hace distincion entre los estados de A y B
   if (estado == HIGH){
      W = W +1;
      delay(500);
      if (W == 60){W = 0;}
      Serial.println(W);
   }
   if (estado1 == HIGH){
      Serial.println("selecciona donde alojar valor");
      Serial.println("1.segundos, 2.minutos, 3.hora, 4.diaSemana, 5.diaMes 6.mes 7.año");
      Serial.println("8.guardar en RTC");
      delay(6000);
      if (Serial.available() != 0){
        W2 = Serial.read();
        switch(W2){
          case 49:
          segundos = W;
          Serial.print("ha sido enviaddo a segundos");
          break;
          
          case 50:
          minutos = W;
          Serial.println("ha sido enviado a minutos");
          break;
          
          case 51:
          hora = W;
          Serial.println("ha sido enviado a hora");
          break;
          
          case 52:
          diaSemana = W;
          Serial.println("ha sido enviado a diaSemana");
          break;
          
          case 53:
          diaMes = W;
          Serial.println("ha sido enviado a diaMes");
          break;
          
          case 54:
          mes = W;
          Serial.println("ha sido enviado a año");
          break;
          
          case 55:
          anio = W;
          case 56:
          Serial.println("Guardando...");
          //zona de comunicacion con el RTC por i2c
          
          Wire.beginTransmission(i2cAddress);
          segundos = (segundos/10*16) + (segundos%10); //BCD
          Wire.write(segundos);
          minutos = (minutos/10*16) + (minutos%10); //BCD
          Wire.write(minutos);
          hora = (hora/10*16) + (hora%10); //BCD
          Wire.write(hora);
          diaSemana = (diaSemana/10*16) + (diaSemana%10); //BCD
          Wire.write(diaSemana);
          diaMes = (diaMes/10*16) + (diaMes%10); //BCD
          Wire.write(diaMes);
          mes = (mes/10*16) + (mes%10); //BCD
          Wire.write(mes);
          anio = (anio/10*16) + (anio%10); //BCD
          Wire.write(anio);
          Wire.endTransmission();
          Serial.println("hecho");
          break;
        
        
        }
      }
   }
  }
 }

