# Testing sobre Arduino IDE
En este directorio van todos los programas que se apoyen de alguna forma en la plataforma Arduino, al margen del chip o microcontrolador utilizado; por ejemplo, buena parte de la colección de programas está pensada para ser programada con una placa de pruebas propia la cual lleva una ESP32, que no tiene nada que ver con las placas arduino pero la comunidad a favorecido su integración en el mismo IDE.

Con el fin de mantener algo de orden, cada programa está organizado según las características y/o periféricos que se hayan utilizado:

1. **Controles básicos**: Aquí se recopila todo el código que se utilice para probar características básicas del MCU que se programa, ya sea el manejo de puertos E/S, Interrupciones, timers y etc.

2. **Control de displays**: Aquí ya nos centramos en periféricos externos y se recopilan los programas utilizados para probar el manejo de diferentes librerías gráficas para diferentes tipos de pantallas.

3. **Control de motores**: Como su nombre bien describe, programas centrados en el control de motores, ya sean los típicos DC, Servos, paso a paso, etc.

4. **Comunicaciones inalámbricas**: En este apartado se programama el control de modulos involucrados en comunicaciones inalámbricas como RF, WiFi, Bluethooth, IR, etc. En el caso particular de la ESP32 ya viene integrado en el mismo chip el wifi y el bluetooth, de modo que por mantener algo de coherencia temática tambien lo agrupo aquí.

5. **Manejo de sensores**: Aquí se prueba la integración de diferentes tipos de sensores según sea la necesidad. Estos bien pueden ser analógicos y su medida consiste en el uso de un ADC o también puede ser un modulo digital que se comunique mediante I2C/SPI o con otro tipo de protocolo.

6. **Miscelánea**: Este es el apartado comodin cuando el resto de categorías no valen. Aquí se prueban integraciones con chips y demás dispositivos que están fuera de las anteriores categorías, por ejemplo RTCs, chips de audio, multiplexores, etc.


