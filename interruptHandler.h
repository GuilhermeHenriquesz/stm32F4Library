#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "stm32f4xx_hal.h"

void interruptiOn(void);
/*
Initiate SYSCFG clock
*/

void interruptPin(GPIO_TypeDef* porta, uint8_t line, uint8_t edge);
/*
Set a pin to interruption
@Param porta-> GPIO port to use
@Param line-> EXTI line to use
@Param edge-> set the edge to detect(values: 0->Falling edge, 1->Rising Edge, 2->Both)
*/

#endif