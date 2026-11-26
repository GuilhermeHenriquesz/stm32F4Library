/**
 * @file adcHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 *
 * @brief Handle with GPIO
 *
 * @date 2026-11-06
 */

#ifndef ADC_HANDLER_H
#define ADC_HANDLER_H

#include "stm32f4xx_hal.h"
#include "timerHandler.h"
#include <stdlib.h>

typedef void (*function)(void);

static volatile function ADC_ISR[1];

enum {
    RES12BITS,
    RES10BITS,
    RES8BITS,
    RES6BITS
};

enum {
    SMP3,
    SMP15,
    SMP28,
    SMP56,
    SMP84,
    SMP112,
    SMP144,
    SMP480
};

enum {
    ADC_PA0,
    ADC_PA1,
    ADC_PA2,
    ADC_PA3,
    ADC_PA4,
    ADC_PA5,
    ADC_PA6,
    ADC_PA7,
    ADC_PB0,
    ADC_PB1,
    ADC_PC0,
    ADC_PC1,
    ADC_PC2,
    ADC_PC3,
    ADC_PC4,
    ADC_PC5
};

/**
 * @brief Start a single channel ADC
 * 
 * @param ADCx ADC to be started
 * @param pin Pin of ADC to be started, see the ADC Pin enum for more information
 * @param resolution Resolution of the ADC, see the ADC Resolution enum for more information
 */
void adcSingleStart(ADC_TypeDef* ADCx, uint8_t pin, uint8_t resolution);

/**
 * @brief Start multiple channels in an ADC
 * 
 * @param ADCx ADC to be started
 * @param pins Array of pins from enum ADC pins to be started, see the ADC Pin enum for more information
 * @param sizePins Size of the array of pins
 * @param resolution Resolution of the ADC, see the ADC Resolution enum for more information
 */
void adcMultiStart(ADC_TypeDef* ADCx, uint8_t pins[], uint8_t sizePins, uint8_t resolution);

/**
 * @brief Get a single channel conversion of an ADC
 * 
 * @param ADCx ADC to get a value
 * @return uint16_t value read in the ADC
 */
uint16_t getAdcSingleConversion(ADC_TypeDef* ADCx);

/**
 * @brief Get multiple channels conversions of an ADC
 * 
 * @param ADCx ADC to get multiple values
 * @param readPins Array of uint16_t to store all the values of the channels
 * @param sizePins Length of the readPins array
 */
void getAdcMultiConversion(ADC_TypeDef* ADCx, uint16_t readPins[], uint8_t sizePins);

/**
 * @brief Add an interruption in an ADC
 * 
 * @param ADCx ADC to be interrupted
 * @param func A function to be executed on the interruption
 */
void initAdcInterrupt(ADC_TypeDef* ADCx, function func);

/**
 * @brief Get an ADC by a interrupt instead of waiting in a while looping
 * 
 * @param ADCx ADC to be readed
 */
void getAdcInterruptConversion(ADC_TypeDef* ADCx);

/**
 * @brief Init the temperature sensor of the STM32
 * 
 */
void adcTemperatureSensor(void);

/**
 * @brief Get the temperature from the temperature sensor
 * 
 * @return float the value of the temperature in Celsius
 */
float getTemperature(void);

/**
 * @brief Extern interruption in an ADC to read the ADCs value
 * 
 * @param ADCx ADC to be interrupted
 * @return int return the value of the ADC
 */
int adcExternInterruptOn(ADC_TypeDef* ADCx);

/**
 * @brief Set up the watch dog ADC that compares values to make an interruption
 * 
 * @param ADCx ADC to be readed
 * @param pin ADC Pin to be readed, see the ADC Pin enum for more information
 * @param highLimit the higher limit to compare
 * @param lowLimit the lower limit to compare
 */
void watchdogAdc(ADC_TypeDef* ADCx, uint8_t pin, uint32_t highLimit, uint32_t lowLimit);

/**
 * @brief Pass a function to oficially enable the watch dog adc
 * 
 * @param ADCx ADC to be readed
 * @param func Function to interrupt
 */
void getWatchdog(ADC_TypeDef* ADCx, function func);

/**
 * @brief Function that encapsulates the functions of ADC interrupt passed by parameter
 * 
 */
void ADC_IRQHandler(void);

#endif
