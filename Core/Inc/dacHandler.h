/**
 * @file dacHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 *
 * @brief Handle with GPIO
 *
 * @date 2026-09-17
 */

#ifndef DAC_HANDLER_H
#define DAC_HANDLER_H

#include "stm32f4xx_hal.h"
#include <stdlib.h>

enum{
    DAC_PA4,
    DAC_PA5
};

enum {
    DHR8R,
    DHR12L,
    DHR12R,
};

enum {
    DISABLEDWAVE,
    NOISEWAVE,
    TRIANGLEWAVE
};

enum {
    AMP1BIT,
    AMP2BITS,
    AMP3BITS,
    AMP4BITS,
    AMP5BITS,
    AMP6BITS,
    AMP7BITS,
    AMP8BITS,
    AMP9BITS,
    AMP10BITS,
    AMP11BITS,
    AMP12BITS
};


void dacStart(uint8_t pin, uint8_t resolution);
void dacStart2(uint8_t pin, uint8_t resolution, uint8_t waveform, uint8_t amplitude);
void dacSetValue(uint8_t pin, uint8_t resolution, uint16_t value);
void dacTrigger(uint8_t pin);


#endif
