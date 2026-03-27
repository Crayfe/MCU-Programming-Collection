import board
import busio
i2c = busio.I2C(board.GP1, board.GP0) 
from ssd1306 import SSD1306_I2C
oled = SSD1306_I2C(128, 32, i2c)
oled.fill(0)
oled.text('Crayfe', 0, 0)
oled.text('Display testing', 0, 10)
oled.show()
