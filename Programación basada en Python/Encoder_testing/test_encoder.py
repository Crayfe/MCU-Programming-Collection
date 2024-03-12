import time
import board
import digitalio

'''
Codigo de prueba de encoder rotativo en CircuitPython 
(by Crayfe) 

Pines necesarios:
clk     ->      GP4
dt      ->      GP3
sw      ->      GP2

'''
#Variables auxiliares
cursor = 0
#st_clk
#last_st_clk

#   SETUP
#Configuracion de los pines. Para el pulsador es necesario habilitar la resistencia pullup
encoder_clk = digitalio.DigitalInOut(board.GP4)
encoder_clk.direction = digitalio.Direction.INPUT

encoder_dt = digitalio.DigitalInOut(board.GP3)
encoder_dt.direction = digitalio.Direction.INPUT

encoder_sw = digitalio.DigitalInOut(board.GP2)
encoder_sw.direction = digitalio.Direction.INPUT
encoder_sw.pull = digitalio.Pull.UP

#Leemos el estado inicial del pin clk
last_st_clk = encoder_clk.value

#   LOOP
while True:
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