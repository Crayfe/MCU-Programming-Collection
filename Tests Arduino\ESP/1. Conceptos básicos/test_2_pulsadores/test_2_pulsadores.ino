
//Programa hecho por Crayfe
//programa que distingue cuando dos botones (A y B) son pulsados

int estado = 0;  //variable que contiene el estado del boton A
int estado1 = 0; //variable que contola el estado del boton B
void setup(){
Serial.begin(9600); //comienza la comunicacion serial
Serial.println("Pulsa A o B"); //muestra en el monitor serial mensaje inicial
pinMode(8, INPUT); //entrada del boton A
pinMode(9, INPUT); //entrada del boton B
}
void loop() {

estadoA = digitalRead(9);   //lee las entradas A y B
estadoB = digitalRead(8);
if (estadoA != estadoB){  //hace distincion entre los estados de A y B
   if (estadoA == HIGH){
    Serial.println("A pulsado"); //caso en el que A esta pulsado
    delay(1000); //Demora de un segundo para no petal el monitor serial del mismo mensaje
   }
   if (estadoB == HIGH){
    Serial.println("B pulsado"); //caso en el que B esta pulsado
    delay(1000); //Demora de un segundo para no petal el monitor serial del mismo mensaje
 
   }
}
if (estadoA && estadoB == HIGH){
Serial.println("A y B pulsados"); //Si ambos botoners estan pulsados, monitorea que ambos lo estan
delay(1000); //Demora de un segundo para no petal el monitor serial del mismo mensaje
}
}
