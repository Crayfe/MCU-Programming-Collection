//Test sensor de proximidad por ultrasonidos (Sensor HC04)
#define triggerPin 4 //D3
#define echoPin 5 //D4

long duracion;
float distancia;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Iniciar elproceso de envío de ultrasonido
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion/2) / 29.1;
  

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println("cm");
  delay(1000);

}
