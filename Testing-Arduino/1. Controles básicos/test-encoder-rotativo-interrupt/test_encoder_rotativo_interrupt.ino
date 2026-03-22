/*
 * Código para probar el funcionamiento de un encoder rotativo con interrupciones.
 *
 *
 * Pines para placa de pruebas (ESP32):
 *
 */

#define CLK_PIN 27
#define DT_PIN 14
#define SW_PIN 12

volatile int cursor = 0;
volatile int last_st_clk;

void IRAM_ATTR handleEncoder() {
  int st_clk = digitalRead(CLK_PIN);
  if (st_clk != last_st_clk) {
    if (digitalRead(DT_PIN) != st_clk) {
      ++cursor;
    } else {
      --cursor;
    }
  }
  last_st_clk = st_clk;
}

void setup() {
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.begin(9600);

  last_st_clk = digitalRead(CLK_PIN);
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), handleEncoder, CHANGE);
}

void loop() {
  noInterrupts();
  int cursor_local = cursor;
  interrupts();

  Serial.print("Cursor: ");
  Serial.println(cursor_local);

  if (!digitalRead(SW_PIN)) {
    Serial.println("Encoder pulsado");
    delay(200);
  }

  delay(100);
}
