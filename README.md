# MCU Programming Collection
En este repositorio recopilo una colección programas sencillos enfocados para testear el funcionamiento de diversas funcionalidades con MCUs basados en Arduino, Raspberry Pi, MicroPython/CircuitPython, y demás. Este repositorio me sirve a mí (@Crayfe) para tener todos mis programas mejor organizados y documentados, además de no perder tiempo repitiendo los mismos pasos a medida que voy cacharreando. Además, tal vez la persona que lea esto encuentre algo que le llame la atención y le sea útil también.

## Dev-board de bajo presupuesto compatible con esp32 y Raspberry pi PICO

![dev-board con una esp32 montada ](dev-board-esp32.jpg)

Para hacer las pruebas me he montado una placa de pruebas como se muestra en la imagen de arriba, con la motivación de ahorrarme tiempo montando componentes en una protoboard y minimizar errores evitables.

Los diferentes códigos de pruebas están separados en los directorios **Plantillas para Dev-board**, **Programación basada en Arduino** y **Programación basada en Python**, dependiendo del lenguaje y hardware utilizado para cada prueba.


## Plantillas para hacer testing con Dev-board
Con el objetivo de agilizar todo tipo de pruebas de funcionalidades e integración de estas en un mismo sitio se ha diseñado una placa para prototipado. Esta placa pretende ser compatible con una dev-board basada en **ESP32** y una **Raspberry Pi PICO**. 

La placa de pruebas dispone de lo siguiente:
- 3 pulsadores NA terminados en gnd (es necesario asignar resistencias pull-up en el software) .
- 1 encoder rotativo.
- 1 buzzer piezoeléctrico.
- 1 display OLED a través de puerto I2C.
- 1 lector de tarjetas microSD a través de puerto SPI.
- Pines para conectar dispositivos externos que usen I2C (GND VDD SCK SDA)
- Pin para sensores digitales que solo necesitan un pin para su lectura (GND VDD DAT).

En este directorio se recopilan unos programas detalladamente documentados, identificando todos los pines utilizables y para qué están destinados estos. Además, se dispone de una colección de funciones para probar los componentes anteriormente mencionados. Como estos programas disponen de lo suficiente para probar y desarrollar funcionalidades más complejas estos programas sirven como plantilla, de ahí su nombre.


## Tests Arduino\ESP
En este directorio se recopilan una colección de programas de testing basados en Arduino, ya que también sirven para los ESP32 y similares. 

En esta colección de pruebas se intenta hacer un barrido general, abarcando características básicas de cualquier microcontrolador (como pueden ser el manejo de pines analógicos y digitales, interrupciones, protocolos de comunicación y demás) ademas de sensores, pantallas, motores y hardware más específico como podría ser el de un ESP32.

### Test codes
- tests_Entradas_Dig_Adc
- Lectura de dos entradas analógicas
- Test comunicación serie y botones A y B
- test_Bluetooth
- test_Distancia_HC04
- test_ESP32_WIFI_AP
- tests_Modulos_RF
    - Receptor
    - Transmisor
- test_Control_IR
- test_DS1307+SSD1306
- test_ESP8266_ADC
- tests_RTC_DS1307
- test_DHTxx
- test_DS18b20

## Tests microPython
En este directorio se recopilan todos los programas de prueba destinado para plataformas basadas en Python, ya sean MicroPython o CircuitPython e independientemente del MCU empleado.

### Test codes
