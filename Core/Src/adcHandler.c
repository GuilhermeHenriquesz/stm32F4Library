#include "adcHandler.h"

void adcStart(ADC_TypeDef* ADCx, uint8_t pin[], uint8_t channelType, uint8_t resolution){

    for (uint8_t i = 0; i < sizeof(pin); i++){
        if (pin[i] < 8){
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port A clock
            GPIOA->MODER &= ~(0b11 << pin[i] * 2);
            GPIOA->MODER |= 0b11 << pin[i] * 2; // Set ANALOG mode
        }

        else if (pin[i] == 8 || pin[i] == 9){
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Activate port B clock
            GPIOA->MODER &= ~(0b11 << (pin[i] - 8) * 2);
            GPIOA->MODER |= 0b11 << (pin[i] - 8) * 2;
        }
        else {
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Activate port C clock
            GPIOA->MODER &= ~(0b11 << (pin[i] - 10) * 2);
            GPIOA->MODER |= 0b11 << (pin[i] - 10) * 2;
        }
    }

    //if(!(RCC->APB2ENR & (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8))
    RCC->APB2ENR |= (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8;

    ADC->CCR |= (0b01 << 16); // Set the prescaler


    if(!channelType)   //SINGLE_CHANNEL
    {
        ADCx->CR1 &= ~ADC_CR1_SCAN; //desabilita o escaneamento de canais
        ADC1->CR2 &= ~ADC_CR2_EOCS;
    }
    else        //MULTI_CHANNEL
    {
        ADCx->CR1 |= ADC_CR1_SCAN;  //habilita o escaneamento de canais
        ADC1->CR2 |= ADC_CR2_EOCS;  //bit EOC setado ao final de cada conversão
    }

    ADCx->CR1 &= ~ADC_CR1_RES;      //limpa o campo da resolução
    ADCx->CR1 |= resolution << 24;

    ADCx->SMPR2 |= 0b111; // Select the sample time

    ADCx->CR2 |= ADC_CR2_ADON;
    Delay_ms(1);    //aguarda o ADC iniciar

    if (sizeof(pin) > 1){
        ADCx->SQR1 &= ~(0xF << 20);
        ADCx->SQR1 |= (sizeof(pin) << 20);
        ADCx->SQR3 &= ~0x1F;
        //ADCx->SQR3 |=  configurar para multiplos canais;
    }
    else {
        ADCx->SQR1 &= ~(0xF << 20);
        ADCx->SQR3 &= ~(0x1F);
        ADCx->SQR3 |= pin;
    }
}

void adcStart2(uint8_t pin, uint8_t channel, uint8_t channelType, uint8_t resolution, uint8_t sampleTime){

}

uint16_t getAdcSingleConversion(ADC_TypeDef* ADCx){
    ADCx->CR2 |= ADC_CR2_SWSTART;
    while (!(ADCx->SR & ADC_SR_EOC));
    return ADCx->DR;
}
