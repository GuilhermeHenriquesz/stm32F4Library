/**
 * @file timerHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 * @brief Handle with temporization functions
 * @date 2026-09-21
 */
#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

#define TIM1

#include "gpioHandler.h"

static uint8_t isInitiated = 0;

typedef void (*function)(void);
static volatile function ISRs[5];

enum {
    UPCOUNTER,
    DOWNCOUNTER,
    UPDOWNCOUNTER
};

/**
 * @brief Initiate the timer delay configs(Timer used is timer 2)
 */
void delayInit(void);

/**
 * @brief Miliseconds delay
 *
 * @param ms miliseconds to be delayed
 */
void delay(uint32_t ms);

/**
 * @brief Microseconds delay
 *
 * @param microSeconds microseconds to be delayed
 */
void microDelay(uint32_t microSeconds);

void sysTick(uint32_t reloadValue); // Clock 168Mhz

void SysTick_Handler();

void timer(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm);

#endif
