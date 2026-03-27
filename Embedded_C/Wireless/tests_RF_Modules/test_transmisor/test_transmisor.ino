//Prueba de recepción y transmision del encendido y apagado de un LED con el modulo RF para Arduino
//Para este test es necesario tener instalada la librería VirtualWire
//test EMISOR
#include <VirtualWire.h>
void setup()
{
    pinMode(12,OUTPUT);
    vw_set_ptt_inverted(true);  // Requerido por el modulo RF
    vw_setup(7000);            // Velocidad de conexion bps
    vw_set_tx_pin(3);         // Pin en el que conectamos la patilla data del transmisor
}
 
void loop()
{
   //Mensaje a enviar:
   const char *msg = "";
   if(digitalRead(12)==HIGH){
     msg = "E";
   }else{msg = "A";}
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx();        // Esperamos a que termine de enviar el mensaje
   delay(200);         // Esperamos para enviar el siguiente mensaje        

}
