//New transmission method.
//In addition, the gdo0 and gdo2 pin are not required.
//https://github.com/LSatan/SmartRC-CC1101-Driver-Lib
//by Little_S@tan
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <SPI.h>
#include <LED_Signal.hpp>

byte transmitt_byte[11] = {72,101,108,108,111,32,87,111,114,108,100};
byte init_conn[3] = {1,2,3};
bool initialzed_conn = false;
char *transmitt_char = "Hello World";


void setup() {

    Serial.begin(9600);

    if (ELECHOUSE_cc1101.getCC1101()){        // Check the CC1101 Spi connection.
      Serial.println("Connection OK");
     digitalWrite(ONBOARD_LED, LOW); //turn the led off
     delay(1000); //wait for 1 sec
     digitalWrite(ONBOARD_LED, HIGH); //turn the led on
     delay(1000); //wait for 1 sec 
    }else{
      Serial.println("Connection Error");
     digitalWrite(ONBOARD_LED, LOW); //turn the led off
     delay(100); //wait for 1 sec
     digitalWrite(ONBOARD_LED, HIGH); //turn the led on
     delay(100); //wait for 1 sec 
    }
    signalIndicator.init();
    ELECHOUSE_cc1101.Init();              // must be set to initialize the cc1101!
    ELECHOUSE_cc1101.setCCMode(1);       // set config for internal transmission mode.
    ELECHOUSE_cc1101.setModulation(0);  // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
    ELECHOUSE_cc1101.setMHZ(433.92);   // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
    ELECHOUSE_cc1101.setSyncMode(2);  // Combined sync-word qualifier mode. 0 = No preamble/sync. 1 = 16 sync word bits detected. 2 = 16/16 sync word bits detected. 3 = 30/32 sync word bits detected. 4 = No preamble/sync, carrier-sense above threshold. 5 = 15/16 + carrier-sense above threshold. 6 = 16/16 + carrier-sense above threshold. 7 = 30/32 + carrier-sense above threshold.
 // ELECHOUSE_cc1101.setPA(10);      // set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12) Default is max!
    ELECHOUSE_cc1101.setCrc(1);     // 1 = CRC calculation in TX and CRC check in RX enabled. 0 = CRC disabled for TX and RX.
//      setSpi();
   delay(100); //wait for 0.1 sec 
   initSettings();
    
}

void initSettings(){
    Serial.println("VERSION:");
    Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x31));
   delay(100); //wait for 1 sec 
    Serial.println("PARTNUM:");
    Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x30));
   delay(100); //wait for 1 sec 
    Serial.println("RSSI:");
    Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0x34));
   delay(100); //wait for 1 sec 
    Serial.println("FREQEST:");
    Serial.println(ELECHOUSE_cc1101.SpiReadStatus(0xF2));
    delay(100);
    Serial.print("Rssi: ");
    Serial.println(ELECHOUSE_cc1101.getRssi());
    Serial.println("Tx Mode");
}


void sendByte(byte arr[]){
  ELECHOUSE_cc1101.SendData(arr, sizeof(arr), 100);
  //signalIndicator.send();
}

  byte buffer[61] = {0};
bool receiveByte(){
  if (ELECHOUSE_cc1101.CheckRxFifo(100)){
    Serial.println("FIFO");
    delay(100);
    if (ELECHOUSE_cc1101.CheckCRC()){   
      Serial.println("Signal received");
      int len = ELECHOUSE_cc1101.ReceiveData(buffer);
      buffer[len] = '\0';
      signalIndicator.receive();
      for (int i = 0; i<len; i++){
        Serial.print(buffer[i]);
        Serial.print(",");
      }
      return true;
    }
  }  
  return false;
}

void initialMsg(){
  while(!initialzed_conn){
  sendByte(init_conn);
  signalIndicator.send();
   delay(100);
   for(int i  = 0; i<10 && !initialzed_conn; i++){
    if(receiveByte()){
      initialzed_conn = true;
      Serial.println("Initialized Connection!");
      signalIndicator.connEst();
    }
   }
    delay(100);
       for(int i  = 0; i<100; i++){
        sendByte(init_conn);            
      }
  }
}


void loop() {
  initialMsg();
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
