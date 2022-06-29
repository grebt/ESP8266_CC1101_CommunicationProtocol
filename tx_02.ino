#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <SPI.h>
#include <LED_Signal.hpp>
#include <CC1101.hpp>

void setup() {
  cc1101.init(9600, 1, 0, 433.92, 2, 1);
}

void loop() {
  bool loop = true;
  cc1101.initialMsg();
  while(loop){
    cc1101.rxTxDemo();
  }
}
