#define DECODE_NEC            // DECODE_SAMSUNG
#include <IRremote.hpp>       // Do not change header order.

constexpr uint8_t IR_RECEIVE_PIN       {2};  // -> PD2 physical Pin 4.

void setup()
{
   Serial.begin(74880);
  
  IrReceiver.begin(IR_RECEIVE_PIN);
  
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
}


void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        // We have an unknown protocol here, print more info
        IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    if (IrReceiver.decodedIRData.protocol == NEC) {  // SAMSUNG
      Serial.print("Command: 0x");
      Serial.println(IrReceiver.decodedIRData.command,HEX);
    }
    IrReceiver.resume();
  } 
}
