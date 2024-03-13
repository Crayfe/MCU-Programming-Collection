
//Programa hecho por Crayfe

int analogIn0 = 0;
int analogIn1 = 0;
void setup(){
  Serial.begin(9600);
  Serial.println("Entradas analogicas");
  }
void loop(){
  delay(500);
  analogIn0 = analogRead(0);
  analogIn1 = analogRead(1);
  Serial.print("canal 0: ");
  Serial.print(analogIn0);
  Serial.print("  Canal 1: ");
  Serial.println(analogIn1);
  

}
