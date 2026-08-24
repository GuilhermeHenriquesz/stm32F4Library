#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include "stm32f4xx_hal.h"
#include <stdlib.h>

typedef struct pin{
	GPIO_TypeDef* porta;
	int pino;
}Pin;
void writeHigh(Pin* pin);
void writeLow(Pin* pin);
void pinStart(Pin **pin, GPIO_TypeDef* porta, int pino);
int readPin(Pin* pin);

#endif