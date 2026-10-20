#include "sevenSegmentsHandler.h"

void writeInDisplay(Pin* pins, uint8_t number){
    for(uint8_t i = 0; i<7 ; i++)
        if((getPinStatus(&pins[i]) << 6 - i) != (~number & (0b1 << (6 - i))))
            togglePin(&pins[i]);

}

void startDisplayPins(Pin *pins){
    for(uint8_t i = 0; i<7 ; i++)
        pinStart(&pins[i], GPIOC, 4+i, OUTPUT);
}
