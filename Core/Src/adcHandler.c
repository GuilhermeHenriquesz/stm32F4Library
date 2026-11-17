#include "adcHandler.h"

void adcStart(ADC_TypeDef* ADCx, uint8_t pins[], uint8_t sizePins, uint8_t resolution){
    for (uint8_t i = 0; i < sizePins; i++){
        if (pins[i] < 8){
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port A clock
            GPIOA->MODER &= ~(0b11 << pins[i] * 2);
            GPIOA->MODER |= 0b11 << pins[i] * 2; // Set ANALOG mode
        }

        else if (pins[i] == 8 || pins[i] == 9){
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Activate port B clock
            GPIOA->MODER &= ~(0b11 << (pins[i] - 8) * 2);
            GPIOA->MODER |= 0b11 << (pins[i] - 8) * 2;
        }
        else {
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Activate port C clock
            GPIOA->MODER &= ~(0b11 << (pins[i] - 10) * 2);
            GPIOA->MODER |= 0b11 << (pins[i] - 10) * 2;
        }
    }

    int deslocamento = 0;
    for (uint8_t i = 0; i < sizePins; i++)
    {
        if(i < 6)
        {
            ADCx->SQR3 &= ~(0x1F << (i * 5));       //limpa os bits do campo do canal
            ADCx->SQR3 |= (pins[i] << (i * 5)); //configura o canal na posição do registrador
        }
        else if(i < 12)
        {
            deslocamento = (i - 6) * 5;
            ADCx->SQR2 &= ~(0x1F << deslocamento);          //limpa os bits do campo do canal
            ADCx->SQR2 |= (pins[i] << deslocamento);    //configura o canal na posição
        }
        else
        {
            deslocamento = (i - 12) * 5;
            ADCx->SQR1 &= ~(0x1F << deslocamento);          //limpa os bits do campo do canal
            ADCx->SQR1 |= (pins[i] << deslocamento);    //configura o canal na posição
        }
    }


    //if(!(RCC->APB2ENR & (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8))
    RCC->APB2ENR |= (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8;

    ADC->CCR |= (0b01 << 16); // Set the prescaler


    //ADCx->SQR1 &= ~(0xF << 20);
    //ADCx->SQR3 &= (sizePins - 1) << 20;

    if (pin[0] == 15){

    }


    if(sizePins == 1)   //SINGLE_CHANNEL
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
}

void adcStart2(uint8_t pin, uint8_t channel, uint8_t resolution, uint8_t sampleTime){

}

uint16_t getAdcSingleConversion(ADC_TypeDef* ADCx){
    ADCx->CR2 |= ADC_CR2_SWSTART;
    while (!(ADCx->SR & ADC_SR_EOC));
    return ADCx->DR;
}

void getAdcMultiConversion(ADC_TypeDef* ADCx, uint16_t readPins[], uint8_t sizePins){
    ADCx->CR2 |= ADC_CR2_SWSTART;
    for (uint8_t i = 0; i < sizePins; i++){
        while(!(ADCx->SR & ADC_SR_EOC));
        readPins[i] = ADCx->DR;
    }
}

void initAdcInterrupt(ADC_Typedef* ADCx, function func) {
    ADC1->CR2 |= ~ADC_CR2_EOCS;  //bit EOC setado ao final de cada sequencia de conversao
    ADCx->CR1 |= ADC_CR1_EOCIE;
    NVIC_EnableIRQ(ADC_IRQn);
    ISR[0] = func;
}

void getAdcInterruptConversion(ADC_Typedef* ADCx) {
    ADCx->CR2 |= ADC_CR2_SWSTART;
}

float adcTemperatureSensor(void){
    ADC->CCR |= 0b01 << 16;
    ADC1->SQR1 &= ~(0xF << 20);
    ADC1->SQR3 |= 16;
    ADC1->SMPR1 |= (7 << 18);
    ADC->CCR |= ADC_CCR_TSVREFE;
    ADC1->CR2 |= ADC_CR2_ADON;

    uint32_t *p = (uint32_t *) 0x1FFF7A2C;
    uint32_t Word = *p;
    uint16_t TS_CAL1 = (Word & 0x0000FFFF);
    uint16_t TS_CAL2 = (Word & 0xFFFF0000);

    ADC1->CR2 |= ADC_CR2_SWSTART;
    while(!(ADC1->SR & ADC_SR_EOC));
    return ((80 * (float) (ADC1->DR - TS_CAL1)) / (TS_CAL2 - TS_CAL1)) + 30;
}

void adcExternInterruptOn(ADC_TypeDef* ADCx, uint8_t pins[], uint8_t sizePins, uint8_t resolution){
    adcStart(ADCx, pins, sizePins, resolution);
    ADC1->CR2 |= 0b01 << 28;
    ADC1->CR2 |= 0b1111 << 24;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTI[2] |= 0b0001 << 12;
    EXTI->RTSR |= 1 << 11;
    EXTI->EMR |= 1 << 1;
}

void ADC_IRQHandler(void){
    if(ISR[0] == NULL) return;
        ISR[0]();
}
