#include "ultrasonicSensorHandler.h"

uint32_t getDistance(Pin* pinEmitter, Pin* pinReceiver){
    uint32_t timeHigh = 0;

    writeHigh(pinEmitter);
    microDelay(10);
    writeLow(pinEmitter);

    while(!readPin(pinReceiver));
    while(readPin(pinReceiver) && timeHigh < 23200){
        timeHigh++;
        microDelay(1);
    }
    return timeHigh/58;
}