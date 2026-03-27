// Pin de control del TIP120 conectado a GPIO 17
const int bombaPin = 17;

void setup() {
  // Configura el pin como salida
  pinMode(bombaPin, OUTPUT);
  // Inicialmente apagado
  digitalWrite(bombaPin, LOW);
}

void loop() {
  // Enciende la bomba
  digitalWrite(bombaPin, HIGH);
  delay(5000); // espera 5 segundos

  // Apaga la bomba
  digitalWrite(bombaPin, LOW);
  delay(5000); // espera otros 5 segundos
}
