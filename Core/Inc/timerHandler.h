/**
 * @file timerHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 * @brief Handle with temporization functions
 * @date 2026-09-21
 */
#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

#include "gpioHandler.h"
#include "stm32f4xx.h"

static uint8_t isInitiated = 0;

typedef struct{
    __IO uint32_t* controlRegister;
    __IO uint32_t* captureCompareMode;
    __IO uint32_t* captureCompare;
} TimerChannel;

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

/**
 * @brief SysTick Configure
 *
 * @param reloadValue Value to reload in the time to be counting down
 */
void sysTick(uint32_t reloadValue); // Clock 168Mhz

/**
 * @brief Timer Configuration
 *
 * @param TIMx Struct TIMER that represents the timer to be configured
 * @param prescaler Value that divides the clock, originally 86Mhz
 * @param reload Value to be putted on the ARR register, reloading the timer each time it ends
 * @param countForm An element of the count form enum that represents the way that the timer will count(ascendent, descendent, up/down)
 */
void timerStart(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm);

/**
 * @brief Set a Timer to interrupt
 * 
 * @param TIMx Struct TIMER to be interrupted
 * @param prescaler Value that divides the clock, originally 86Mhz
 * @param reload Value to be putted on the ARR register, reloading the timer each time it ends
 * @param countForm An element of the count form enum that represents the way that the timer will count(ascendent, descendent, up/down)
 * @param func A function that will execute every reset event of the timer
 */
void timerInterruption(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm, function func);

//void timerPWM(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm);

/**
 * @brief Start up the timer channel
 * 
 * @param toStart Struct TimerChannel that represents the channel
 * @param timer Struct TIMER to get the timerChannel attributes
 * @param channel Value between 1 and 4 that represents the channel
 */
void timerChannelStart(TimerChannel* toStart, TIM_TypeDef* timer, uint8_t channel);

/**
 * @brief Set the DutyCycle of a PWM channel
 * 
 * @param channel Struct TimerChannel to update the duty value
 * @param duty The value to be passed to be the duty cycle
 */
void setDuty(TimerChannel* channel, uint32_t duty);

/**
 * @brief Get the Timer time
 * 
 * @param TIMx Struct TIMER to get time
 * @return uint32_t the value of the register CNT that represents the value of the time passed
 */
uint32_t getTimer(TIM_TypeDef* TIMx);

/**
 * @brief Resets timer count
 * 
 * @param TIMx Struct TIMER to be reseted
 */
void resetTimer(TIM_TypeDef* TIMx);

#endif
