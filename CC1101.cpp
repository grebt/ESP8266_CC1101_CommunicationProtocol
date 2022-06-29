#include "CC1101.hpp"
#include <ELECHOUSE_CC1101_SRC_DRV.h>


byte buffer[61] = {0};
bool initialzed_conn = false;
byte init_conn[3] = {42, 23, 11};

CC1101Protocol::CC1101(int baud, int ccMode, int modulation, double mHz, int syncMode, int crc){
    Serial.begin(baud);
    if (ELECHOUSE_cc1101.getCC1101()){ 
        Serial.println("Initialized");
        Serial.print("Version: ");
        Serial.print(ELECHOUSE_cc1101.SpiReadStatus(0x31));
    }else{
        Serial.println("Failed - going to break...");
        return;
    }
    ELECHOUSE_cc1101.Init();             
    ELECHOUSE_cc1101.setCCMode(ccMode);       
    ELECHOUSE_cc1101.setModulation(modulation);  
    ELECHOUSE_cc1101.setMHZ(mHz);   
    ELECHOUSE_cc1101.setSyncMode(syncMode); 
    ELECHOUSE_cc1101.setCrc(crc);     
}

void CC1101Protocol::sendByte(byte arr[]){
  ELECHOUSE_cc1101.SendData(arr, sizeof(arr), 100);
}


bool CC1101Protocol::receiveByte(void){
  if (ELECHOUSE_cc1101.CheckRxFifo(100)){
    delay(10);
    if (ELECHOUSE_cc1101.CheckCRC()){   
      Serial.println("Signal received");
      int len = ELECHOUSE_cc1101.ReceiveData(buffer);
      buffer[len] = '\0';
      for (int i = 0; i<len; i++){
        Serial.print(buffer[i]);
        Serial.print(",");
      }
      return true;
    }
  }  
  return false;
}

void CC1101Protocol::initialMsg(void){
  while(!initialzed_conn){
    sendByte(init_conn);
    delay(100);
    for(int i  = 0; i<10 && !initialzed_conn; i++){
        if(receiveByte()){
        initialzed_conn = true;
        for(int i = 0; i < sizeof(init_conn) && initialzed_conn; i++){
            Serial.println(byte[i]);
            if(byte[i] != init_conn[i]){
                initialzed_conn = false;
            }
        }
        }
   }
    Serial.println("Initialized Connection!");
    delay(100);
       for(int i  = 0; i<100; i++){
        sendByte(init_conn);            
      }
  }
}

void CC1101Protocol::rxTxDemo(void){
    bool received = false;
    while(true){
        sendByte(init_conn);
        delay(10);
        for(int i  = 0; i<10 && !received; i++){
            if(receiveByte()){
                received = true;
            }
        }
    }
    Serial.println("passed!");
    delay(100);
       for(int i  = 0; i<100; i++){
            sendByte(init_conn);            
        }
  }


CC1101Protocol cc1101;
