#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include "stm32f4xx_hal.h"
#include <stdlib.h>

typedef struct pin{
	GPIO_TypeDef* port;
	int index;
}Pin;

enum{
	INPUT,
	OUTPUT,
	ALTERNATE,
	ANALOG
}

void delay(int ms);

void writeHigh(Pin* pin);

void writeLow(Pin* pin);

void togglePin(Pin* pin);

void virtualPwmWrite(Pin* pin, int value);
//@Param value -> value between 0 and 100 that represents the percentage for PWM value

void pinStart(Pin *pin, GPIO_TypeDef* port, int index, int mode);

void setPullDown(Pin* pin)

void setPullUp(Pin* pin)

int readPin(Pin* pin);

#endif