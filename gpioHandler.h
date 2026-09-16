#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include "stm32f4xx_hal.h"
#include <stdlib.h>

typedef struct pin{
	GPIO_TypeDef* port;
	uint8_t index;
}Pin;

enum{
	INPUT,
	OUTPUT,
	ALTERNATE,
	ANALOG
}

void delay(uint8_t ms);

void writeHigh(Pin* pin);

void writeLow(Pin* pin);

void togglePin(Pin* pin);

uint8_t getPinStatus(Pin* pin);

void virtualPwmWrite(Pin* pin, uint8_t value);
//@Param value -> value between 0 and 100 that represents the percentage for PWM value

void pinStart(Pin *pin, GPIO_TypeDef* port, uint8_t index, uint8_t mode);

void setPullDown(Pin* pin)

void setPullUp(Pin* pin)

uint8_t readPin(Pin* pin);

#endif