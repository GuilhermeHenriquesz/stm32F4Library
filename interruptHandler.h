#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "gpioHandler.h"

typedef void (*function)(void);

static volatile function ISRs[7];

//Functions to handle with interruptions
void EXTI0_IRQHandler(void);

void EXTI1_IRQHandler(void);

void EXTI2_IRQHandler(void);

void EXTI3_IRQHandler(void);

void EXTI4_IRQHandler(void);

void EXTI9_5_IRQHandler(void);

void EXTI15_10_IRQHandler(void);



void interruptiOn(void);
/*
Initiate SYSCFG clock
*/

void interruptPin(Pin* pin, uint8_t edge, uint8_t priority, function func);
/*
Set a pin to interruption
@Param edge-> set the edge to detect(values: 0->Falling edge, 1->Rising Edge, 2->Both)
@Param priority-> set the priority of the interruption
@Param func-> set the function to handle with the interruption
*/

#endif