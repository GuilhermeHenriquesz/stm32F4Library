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

void adcSingleStart(ADC_TypeDef* ADCx, uint8_t pin, uint8_t resolution);

void adcMultiStart(ADC_TypeDef* ADCx, uint8_t pins[], uint8_t sizePins, uint8_t resolution);

uint16_t getAdcSingleConversion(ADC_TypeDef* ADCx);

void getAdcMultiConversion(ADC_TypeDef* ADCx, uint16_t readPins[], uint8_t sizePins);

void initAdcInterrupt(ADC_Typedef* ADCx, function func);

void getAdcInterruptConversion(ADC_Typedef* ADCx);

void adcTemperatureSensor(void);

float getTemperature(void);

int adcExternInterruptOn(ADC_TypeDef* ADCx);

void watchdogAdc(ADC_TypeDef* ADCx, uint8_t pin, uint32_t highLimit, uint32_t lowLimit);

void getWatchdog(ADC_TypeDef* ADCx, function func);

void ADC_IRQHandler(void);

#endif
