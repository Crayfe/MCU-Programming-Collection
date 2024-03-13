/*
 * Código para probar el funcionamiento de un encoder rotativo con interrupciones.
 *
 * 
 * Pines para placa de pruebas (ESP32):
 *
 
 #define CLK_PIN 27
 #define DT_PIN 14
 #define SW_PIN 12
 
 * 
 * Pines para Arduino UNO:
 *
 
#define CLK_PIN 6
#define DT_PIN 7
#define SW_PIN 8
 
 * 
 */

#define CLK_PIN 27
#define DT_PIN 14
#define SW_PIN 12

int cursor = 0;
int st_clk;
int last_st_clk;

void setup() {
  pinMode(CLK_PIN,INPUT);
  pinMode(DT_PIN,INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  last_st_clk = digitalRead(CLK_PIN);   //Cargamos el estado inicial y previo del pin CLK

}

void loop() {
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
