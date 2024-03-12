'''
    TEST_HID_BUTTONS

    Código de prueba del funcionamiento del dispositivo de interfaz humana (HID)
    Se van a utilizar tres botones encargados de subir y bajar el volumen y mutear
    (by Crayfe)
'''
import time
import board
import digitalio
import usb_hid
from adafruit_hid.consumer_control import ConsumerControl
from adafruit_hid.consumer_control_code import ConsumerControlCode

kbd = ConsumerControl(usb_hid.devices)

btn1 = digitalio.DigitalInOut(board.GP22)
btn1.direction = digitalio.Direction.INPUT
btn1.pull = digitalio.Pull.UP

btn2 = digitalio.DigitalInOut(board.GP21)
btn2.direction = digitalio.Direction.INPUT
btn2.pull = digitalio.Pull.UP

btn3 = digitalio.DigitalInOut(board.GP20)
btn3.direction = digitalio.Direction.INPUT
btn3.pull = digitalio.Pull.UP

while True:
    if not btn1.value:
        kbd.send(ConsumerControlCode.MUTE)
    if not btn2.value:
        kbd.send(ConsumerControlCode.VOLUME_INCREMENT)
    if not btn3.value:
        kbd.send(ConsumerControlCode.VOLUME_DECREMENT)
        
    time.sleep(0.1)  #Retardo anti-rebotes
