#ifndef CC1101
#define CC1101

#include <Arduino.h>

class CC1101Protocol{

public:
    void init(int baud, int ccMode, int modulation, double mHz, int syncMode, int crc);
    void sendByte(byte arr[]);
    bool receiveByte(void);
    void initialMsg(void);
    void rxTxDemo(void);

};

extern CC1101Protocol cc1101;

#endif