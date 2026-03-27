/*
 * Programa para probar el funcionamiento de un led RGB,
 * Aunque el mismo programa puede ser utilizado para controlar
 * una tira de leds rgb si están montados de forma similar,
 * sin embargo es cierto que se necesitarán adicionalmente unos transistores
 * para suministrar 12V y una corriente considerable en función de la
 * cantidad de leds rgb conectados
 */

/* Un LED RGB consta de 4 pines:
 *  R   Ánodo LED rojo
 *  B   Ánodo LED azul
 *  G   Ánodo LED verde
 *  -   Cátodo común
 */

 /* Para el control de este led se necesitan 3 pines de salida.
  * Si encendemos y apagamos cada led tendríamos una variedad de
  * colores muy limitada, pero si jugamos con las intensidades de
  * cada led obtendremos todo tipo de colores. Entonces necesitamos
  * pines que sean compatibles con PWM, simulando tensiones variables. 
  * 
  * En arduino UNO los pines aptos para PWM son 11, 10, 9, 6 y 5
  * En ESP32 todos los pines son aptos para salida PWM excepto del pin 34 al 39
  * IMPORTANTE: En los ESP el manejo de los pines con PWM varía con respecto a un Arduino
  */

#define rLEDpin 21     //Anodo led rojo
#define bLEDpin 19     //Anodo led azul
#define gLEDpin 18     //Anodo led verde

#define frec 5000   //frecuecia del PWM. En ESP32 se admite desde 1-40000Khz
#define redChan 0   //Canal PWM
#define blueChan 1   //Canal PWM 
#define greenChan 2   //Canal PWM  
#define res 8       //Resolución PWM

void setup(){
// configuración para esp32

ledcSetup(redChan, frec, res);
ledcAttachPin(rLEDpin, redChan);

ledcSetup(blueChan, frec, res);
ledcAttachPin(bLEDpin, blueChan);

ledcSetup(greenChan, frec, res);
ledcAttachPin(gLEDpin, greenChan);

}
void loop(){
  singleFade(0);
  delay(1000);
  singleFade(1);
  delay(1000);
  singleFade(2);
  delay(1000);
  crossFade();
  delay(1000);
}

void singleFade(int chanPWM){
  //Incremento de brillo
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(chanPWM, dutyCycle);
    delay(10);
  }
  //Decremento de brillo  
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(chanPWM,dutyCycle);
    delay(10);
  } 
}
void crossFade(){
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(redChan, dutyCycle);
    ledcWrite(greenChan, 255 - dutyCycle);
    ledcWrite(blueChan, 0);
    delay(15);
  }
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(redChan, 255 - dutyCycle);
    ledcWrite(greenChan, 0);
    ledcWrite(blueChan, dutyCycle);
    delay(15);
  }
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    ledcWrite(redChan, 0);
    ledcWrite(greenChan, dutyCycle);
    ledcWrite(blueChan, 255 - dutyCycle);
    delay(15);
  }
  //Limpiamos los canales
  ledcWrite(redChan, 0);
  ledcWrite(greenChan, 0);
  ledcWrite(blueChan, 0);
  
}
