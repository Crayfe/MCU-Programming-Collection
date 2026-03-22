/*      ESP32_TESTING_TEMPLATE
       
  Plantilla para usar la placa Az-Delivery ESP32-WROOM-32 junto 
  con placa de desarrollo personal (by Crayfe)

  La placa de desarrollo consta de los siguientes componentes:
    - 3 pulsadores simples conectados a gnd
    - 1 encoder rotativo HW-040
    - 1 buzzer CEM-1203(42)
    - 1 Display OLED basado en el chip ssd1306 de 128x64 pixeles
    - 1 Pin de datos para dispositivos tipo DHTxx o Dallas

  Pines necesarios y asignación:
    - 1 pin de entrada digital por cada pulsador
        +   Pulsador 1      ->  25
        +   Pulsador 2      ->  33
        +   Pulsador 3      ->  32
    - 4 pines de entrada digital para encoder rotativo
        +   CLK             ->  27
        +   DT              ->  14
        +   SW              ->  12
    - 1 pin de salida digital para buzzer
        +   Sonido piezo    ->  26
    - 1 pin para leer datos de un sensor digital (Para un DGTxx por ejemplo
        +   DHTxx           ->  4
    - 2 pines para bus de datos i2c (sda y scl) para display
        +   SDA             ->  21
        +   SCL             ->  22
          *La dirección del dispositivo es 0x3C 
           y los pines de datos se establecen por defecto
*/


/*  
 *          LIBRERÍAS NECESARIAS 
 *  para hacer funcionar los componentes anteriormente mencionados.
 */

/*
 *  Para utilizar el display OLED depende de cómo se implemente,
 *  las dependencias y variables pueden variar. En este caso se 
 *  van a utilizar las librerías de Adafruit. Importante tener 
 *  dichas librerías instaladas en el directorio correspondiente
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
 *  Para utilizar un sensor DHTxx
 */
 
#include "DHT.h"

/*  
 *          VARIABLES Y DEFINICIONES NECESARIAS 
 *  para hacer funcionar los componentes anteriormente mencionados.
 */

/*
 *  Para display OLED I2C
 */
#define SCREEN_WIDTH 128 // El ancho del display en pixeles
#define SCREEN_HEIGHT 64 // El alto del display en pixeles
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C // La dirección i2c del display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*
 *  Para generar tonos con el buzzer piezoelectrico necesitamoq
 *  definir el pin de la señal y seleccionar un canal PWM
 */
#define TONE_OUTPUT_PIN 26
#define TONE_PWM_CHANNEL 0

/*
 *  Definimos los pines de los pulsadores
 */
#define BTN1_PIN 25
#define BTN2_PIN 33
#define BTN3_PIN 32

/*
 *  Definimos los pines que necesita el encoder rotativo
 */
#define CLK_PIN 27
#define DT_PIN 14
#define SW_PIN 12

/*
 *  Definimos un pin para leer un sensor DHTxx
 */
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float humedad;
float temperatura;

/*  
 *  Variables auxiliares necesarias para el encoder 
 */
int cursor = 0;
int st_clk;
int last_st_clk;


void setup() {
  
  /*  
   *  En el caso de que queramos realizar comprobaciones mendiante 
   *  comunicaciones serie iniciamos el mismo. 
   *  
   *  El ESP32 puede enviar mensajes a 115200 baudios
   */
   
  Serial.begin(9600);
  dht.begin();
  /*  
   *  Si se va a utilizar el display comprobamos que este funcione.
   *  En el caso de que no funcionase se notifica por el puerto serie
   */
   
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
     Serial.println(F("SSD1306 allocation failed"));
   display.clearDisplay();  //Borramos el splash screen de Adafruit
   display.display();
 
   /*
    *  Inicializamos los pulsadores, que deben programarse para
    *  que funcionen con las resistencias pull-up internas. De este
    *  modo se obtendrán las siguientes lecturas:
    *     Botón en reposo   ->    1
    *     Botón pulsado     ->    0
    *  
    */
/*   
   pinMode(BTN1_PIN, INPUT_PULLUP);
   pinMode(BTN2_PIN, INPUT_PULLUP);
   pinMode(BTN3_PIN, INPUT_PULLUP);
*/
   /*
    *  Inicializamos los pines del encoder y su estado previo
    */
/*
   pinMode(CLK_PIN,INPUT);
   pinMode(DT_PIN,INPUT);
   pinMode(SW_PIN, INPUT_PULLUP);
   Serial.begin(9600);
   last_st_clk = digitalRead(CLK_PIN);   //Cargamos el estado inicial y previo del pin CLK
*/
}

void loop() {
  //test_encoder();
  //test_buttons_state();
  //test_buttons_pulsed();
  test_display();
  //test_tones();
  //test_tones_holded();
  //test_dht(true);
  //delay(2000);
}
/*
 *    FUNCIONES DE TESTING
 */

/*
 *  Funcion para probar la correcta lectura y manejo del encoder
 */
void test_encoder(){
  st_clk = digitalRead(CLK_PIN);
  if(st_clk != last_st_clk){
      if (digitalRead(DT_PIN) != st_clk){
        ++cursor;
      }else{
        --cursor;
      }
      Serial.print("Cursor: ");
      Serial.println(cursor);
   }
  last_st_clk = st_clk;       // Mantenemos el último valor
  bool sw = digitalRead(SW_PIN);
  if(!sw){
    Serial.println("Encoder pulsado");
    delay(200);               // Retardo para descartar rebotes y falsos pulsados
  }
}

/*
 *  Funciones para probar la correcta lectura de los pulsadores
 */
void test_buttons_state(){
  bool btn_state;
  Serial.print("Pulsador 1:");
  btn_state = digitalRead(BTN1_PIN);
  Serial.println(btn_state);
  Serial.print("Pulsador 2:");
  btn_state = digitalRead(BTN2_PIN);
  Serial.println(btn_state);  
  Serial.print("Pulsador 3:");
  btn_state = digitalRead(BTN3_PIN);
  Serial.println(btn_state);
  delay(1000);    
}
void test_buttons_pulsed(){
  if(digitalRead(BTN1_PIN) == LOW){
    Serial.println("bt1 pulsado"); 
    delay(200);
  }
  if(digitalRead(BTN2_PIN) == LOW){
    Serial.println("bt2 pulsado");
    delay(200); 
  }
  if(digitalRead(BTN3_PIN) == LOW){
    Serial.println("bt3 pulsado");
    delay(200); 
  }
}

/*
 *  Funciones para probar la reproducción de diferentes tonos con el
 *  buzzer
 */
 void test_tones(){
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 4);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 4);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_G, 4);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250);
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 5);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
  delay(250); 
 }
 
 void test_tones_holded(){
  ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_D, 4);
  delay(500);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_E, 4);
  delay(500);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_F, 4);
  delay(500);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_G, 4);
  delay(500);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_A, 4);
  delay(500);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_B, 4);
  delay(500);
  ledcWriteNote(TONE_PWM_CHANNEL, NOTE_C, 5);
  delay(500);
  ledcDetachPin(TONE_OUTPUT_PIN);
 }
 /*
  *  Funcion para probar diferentes representaciones en el Display
  */
 void test_dht(bool OLED){
  humedad = dht.readHumidity();
  temperatura = dht.readTemperature();
  //Verificamos datos válidos
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.print("Fallo de lectura del sensor DHT");
    Serial.println(DHTTYPE);
    delay(2000);
    return;
  }
  if(!OLED){
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("% Temperatura: ");
    Serial.print(temperatura);
    Serial.println("ºC");
  }else{
    display.clearDisplay();
    display.cp437(true);
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 5);
    display.print(temperatura);
    display.print(char(9));
    display.println("C");
    display.setCursor(10, 35);
    display.print(humedad);
    display.println("%");
    display.display();
  }
    delay(2000);        //Esperamos 2 segundos
 }
 void test_display(){
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
