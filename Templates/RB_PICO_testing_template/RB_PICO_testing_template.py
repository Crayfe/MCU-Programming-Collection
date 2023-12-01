'''     RB_PICO_TESTING_TEMPLATE

    Plantilla para usar la placa Raspbberry Pi PICO junto con 
    la placa de desarrollo personal (by Crayfe)

    La placa de desarrollo consta de los siguientes componentes:
    - 3 pulsadores simples conectados a gnd
    - 1 encoder rotativo HW-040
    - 1 buzzer CEM-1203(42)
    - 1 Display OLED basado en el chip ssd1306 de 128x64 pixeles

  Pines necesarios y asignación:
    - 1 pin de entrada digital por cada pulsador
        +   Pulsador 1      ->  0
        +   Pulsador 2      ->  0
        +   Pulsador 3      ->  0
    - 4 pines de entrada digital para encoder rotativo
        +   CLK             ->  GP4
        +   DT              ->  GP3
        +   SW              ->  GP2
    - 1 pin de salida digital para buzzer
        +   Sonido piezo    ->  0
    - 2 pines para bus de datos i2c (sda y scl) para display
        +   SDA             ->  GP0
        +   SCL             ->  GP1
          *La dirección del dispositivo es 0x3C 
           y los pines de datos se establecen por defecto

'''
import time
import board
import digitalio
import busio
from ssd1306 import SSD1306_I2C

#   SETUP
#Configuración del display oled
i2c = busio.I2C(board.GP1, board.GP0) 
oled = SSD1306_I2C(128, 64, i2c)

#Configuracion de los pines para el encoder. Para el pulsador es necesario habilitar la resistencia pullup
encoder_clk = digitalio.DigitalInOut(board.GP4)
encoder_clk.direction = digitalio.Direction.INPUT

encoder_dt = digitalio.DigitalInOut(board.GP3)
encoder_dt.direction = digitalio.Direction.INPUT

encoder_sw = digitalio.DigitalInOut(board.GP2)
encoder_sw.direction = digitalio.Direction.INPUT
encoder_sw.pull = digitalio.Pull.UP

#Configuración de los pulsadores
BTN1_PIN = digitalio.DigitalInOut(board.GP2)
BTN1_PIN.direction = digitalio.Direction.INPUT
BTN1_PIN.pull = digitalio.Pull.UP

BTN2_PIN = digitalio.DigitalInOut(board.GP2)
BTN2_PIN.direction = digitalio.Direction.INPUT
BTN2_PIN.pull = digitalio.Pull.UP

BTN3_PIN = digitalio.DigitalInOut(board.GP2)
BTN3_PIN.direction = digitalio.Direction.INPUT
BTN3_PIN.pull = digitalio.Pull.UP

'''
        FUNCIONES DE TESTING
'''

#Función de test para encoder
def test_encoder():
    st_clk = encoder_clk.value
    if st_clk != last_st_clk:
        if encoder_dt.value != st_clk:
            cursor = cursor + 1
        else:
            cursor = cursor - 1
        print("Cursor: ")
        print(cursor)
        print("\r")
    last_st_clk = st_clk
    if not encoder_sw.value:
        print("Encoder pulsado \r")
        time.sleep(0.2)

#Función de test para display
def test_display():
    oled.fill(0)
    oled.text('Crayfe', 0, 0)
    oled.text('Display testing', 0, 10)
    oled.show()

#Función de test para botones


#Función de test para buzzer


'''
        BUCLE PRINCIPAL
'''
while True:
    test_encoder()
    #test_display()
    #test_buttons()
    #test_tones()
    #time.sleep(2)
