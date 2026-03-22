//Este programa sirve para establecer una fecha en un RTC basado en un DS1307
//Se define en este códico la hora y fecha deseada, para luego cargar el progama en el arduino y que éste se comunique
//con el DS1307 y se establezca la hora y fecha fijada. Una vez hecho esto se debe cargar otro programa para no
//reescribir la fecha.
#include <Wire.h>
byte segundos = 0;
byte minutos = 0;
byte hora = 0;
byte diaSemana = 1;
byte diaMes = 11;
byte mes = 6;
byte anio = 12;
byte var = 0;
void setup(){

 Serial.begin(9600);
  Wire.begin();
  Serial.println("¿listo para transmitir?");
}
void loop(){
         
       if (Serial.available() != 0){ 
         var = Serial.read();
         if (var == 49){
          Wire.beginTransmission(0x68);
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
          var = 0;
          Serial.println("hecho");
         
            }    
   }    
 }
