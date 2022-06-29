//New transmission method.
//In addition, the gdo0 and gdo2 pin are not required.
//https://github.com/LSatan/SmartRC-CC1101-Driver-Lib
//by Little_S@tan
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
  //Serial.println("stopped");
  //startCommunication();
//3 different methods to send data without gdo
//When sending, we give a little time to completely transmit the message (time in millis).
//You can shorten the time. It depends on the data rate and the packet length. Just try it out for fine tuning.

//Transmitt "Hello World" from byte format.
//ELECHOUSE_cc1101.SendData(transmitt_byte, 11, 100);
//sendSignal();
//delay(2000);
  
//
////Transmitt "Hello World" from char format.
//ELECHOUSE_cc1101.SendData(transmitt_char, 100);
//sendSignal();
//
////Transmitt "Hello World" from char format directly.
//ELECHOUSE_cc1101.SendData("Hello World", 100);
//sendSignal();
//  Serial.println("RXBYTES:");
//  Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x3B));
//delay(2000);
}
