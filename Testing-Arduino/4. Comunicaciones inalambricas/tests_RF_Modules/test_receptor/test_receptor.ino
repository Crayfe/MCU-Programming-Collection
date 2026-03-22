//Prueba de recepción y transmision del encendido y apagado de un LED con el modulo RF para Arduino
//Para este test es necesario tener instalada la librería VirtualWire
//test RECEPTOR
#include <VirtualWire.h>
 
 void setup(){
    Serial.begin(9600);         // Configuramos la conexion serie con el ordenador
    vw_set_ptt_inverted(true);  // Requerido por el modulo RF
    vw_setup(7000);             // Velocidad de conexion bps
    vw_set_rx_pin(22);          // Pin en el que conectamos la patilla data del receptor
    vw_rx_start();              // Arrancamos el receptor
    pinMode(31,OUTPUT);
 }
 
 void loop(){
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)){
    int i;
    // Mensaje con un chequeo correcto.    
    for (i = 0; i < buflen; i++){
      if(buf[i]=='E')digitalWrite(31,HIGH);
      else if(buf[i]=='A')digitalWrite(31,LOW);
      Serial.write(buf[i]);  // Los datos recibidos son guardados en el buffer
                            // y enviados por el puerto serie al ordenador
    }
    Serial.println();
  }
}
