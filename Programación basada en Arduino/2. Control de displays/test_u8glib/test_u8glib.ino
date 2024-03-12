/* Menu hecho con Encoder y Display LCD (I2C) by: http://elprofegarcia.com/
   Encoder comprado en: http://dinastiatecnologica.com/producto/sensor-de-rotacion-codificador-rotatorio/
 Debe instalar la libreria LiquidCrystal_I2C para que le funcione el programa
 Conexion del Encoder al Arduino
 Encoder---->  Arduino
 CLK            2      
 DT             3
 SW             4
 +              5V
 GND            GND  
  
 Conexiones del I2C al Arduino:
 I2C ---->  Arduino
 SCL        A5      
 SDA        A4
 VCC        5V
 GND        GND  
 
Conexion de los LEDs
Rojo ---> Pin8
Azul ---> Pin9
Verde --> Pin10
Amarillo> Pin11
Blanco--> Pin12
 
*/

#define DT  16       // DT a pin digital 2 (DT en modulo) Pin de la interrupcion 
#define CLK  17      // CLK a pin digital 3 (CLK en modulo)
#define btn 4       // Swiche del encoder al pin 4


char *menu1[] = {"1.Rojo ", "2.Azul ", "3.Verde","4.Amari", "5.Blanc", "6.OFF  "}; // Arreglo del Menu 1
volatile int posicion_encoder = 0; // Posicion del encoder
int ant_posicion = 0;    // Valor anterior de la posicion del encoder

void setup() {
  pinMode(DT, INPUT);   
  pinMode(CLK, INPUT);    
  pinMode(btn, INPUT_PULLUP);    // Entrada con resistencia Pullup para el Switch del encoder


  attachInterrupt(digitalPinToInterrupt(DT), encoder, LOW);  // Se habilita interrupcion en pin 2 modo LOW
  Serial.begin(9600);   // incializa puerto serie a 9600 bps
  Serial.println("SENSOR ROTACION");  // Mensaje inicial en Puerto Serie
}

void loop() {
  if (digitalRead(btn) == LOW)     // Si es oprimido el Swich del Encoder
    {
      
   
      Serial.println(menu1[posicion_encoder]); // Muestra el valor de la posicion del  menu 
      
      delay(700);                 // retardo para que no se lea varias veces el swich del Encoder
      
    }
    
  if (posicion_encoder != ant_posicion) { // Si la posicion del menu es  distinta a la anterior
    Serial.println(menu1[posicion_encoder]); // muestra la nueva posicion del Menu
    ant_posicion = posicion_encoder ; // actualiza la posicion del menu
  }
}




void encoder()  {                //Funcion que determina el sentido del giro del encoder
  static unsigned long ultimaInterrupcion = 0;  // variable static con ultimo valor de
                                                // tiempo de interrupcion
  unsigned long tiempoInterrupcion = millis();  // variable almacena valor de func. millis

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {  // No lee posibles rebotes en pulsos menores a 5 mseg.
    if (digitalRead(CLK) == HIGH)     // si CLK es HIGH, rotacion a la derecha
    {
      posicion_encoder++ ;        // incrementa posicion del menu en 1
    }
    else {          // si CLK es LOW, rotacion a la izquierda
      posicion_encoder-- ;        // decrementa posicion del menu en 1
    }

    //posicion_encoder = min(5, max(0, posicion_encoder));  // numero de opciones del Menu, inferior 0 superior en 5
    ultimaInterrupcion = tiempoInterrupcion;  //actualiza valor del tiempo tiempo
  }           
}
