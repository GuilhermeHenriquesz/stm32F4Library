/**
 * @file interruptHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 * @brief Handle with interruptions
 * @date 2026-09-17
 * @see gpioHandler.h
 */

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include "gpioHandler.h"

typedef void (*function)(void);

static volatile function ISRs[7];

/**
 * @brief Enumerate to pin interrupt states
 * @details In the stms registers, the bits that defines the edge of the interruption is setted by putting 1 in the falling register or rising register, this enum abstracts the values of the edge param of the interruptPin function
 * @see interruptPin
 */
enum{
    FALLING,
    RISING,
    FALLING_AND_RISING
};

//Functions to handle with interruptions
void EXTI0_IRQHandler(void);

void EXTI1_IRQHandler(void);

void EXTI2_IRQHandler(void);

void EXTI3_IRQHandler(void);

void EXTI4_IRQHandler(void);

void EXTI9_5_IRQHandler(void);

void EXTI15_10_IRQHandler(void);


/**
 * @brief Initiate SysCfg clock to enable interruptions
 */
void interruptiOn(void);

/**
 * @brief Set up the interruption in a pin
 *
 * @param pin Pin to be setted
 * @param edge Edge to set up the interruption
 * @param priority Priority to set up the interruption
 * @param func Function to be executed when the interruption occurs
 */
void interruptPin(Pin* pin, uint8_t edge, uint8_t priority, function func);

#endif