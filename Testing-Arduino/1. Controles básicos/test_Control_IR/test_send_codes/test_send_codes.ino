#include <IRremote.h>

IRsend ir;

void setup() {
  // put your setup code here, to run once:
  ir.sendSAMSUNG(0xE0E040BF, 32);
  delay(10000);
  ir.sendSAMSUNG(0xE0E09E61, 32);
    delay(5000);
  ir.sendSAMSUNG(0xE0E046B9, 32);
    delay(1000);
  ir.sendSAMSUNG(0xE0E016E9, 32);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
