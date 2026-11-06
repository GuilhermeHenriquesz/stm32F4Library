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
    PA4,
    PA5
};

enum {
    DHR8R,
    DHR12L,
    DHR12R,
    DHR8RD,
    DHR12LD,
    DHR12RD

};


void dacStart(uint8_t pin, uint8_t bits, uint8_t channel);
void dacStart(uint8_t pin);


#endif
