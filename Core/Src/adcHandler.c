#include "adcHandler.h"


void adcMultiStart(ADC_TypeDef* ADCx, uint8_t pins[], uint8_t sizePins, uint8_t resolution){
    for (uint8_t i = 0; i < sizePins; i++){
        if (pins[i] < 8){
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port A clock
            GPIOA->MODER &= ~(0b11 << pins[i] * 2);
            GPIOA->MODER |= 0b11 << pins[i] * 2; // Set ANALOG mode
        }

        else if (pins[i] == 8 || pins[i] == 9){
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Activate port B clock
            GPIOB->MODER &= ~(0b11 << (pins[i] - 8) * 2);
            GPIOB->MODER |= 0b11 << (pins[i] - 8) * 2; // Set ANALOG mode
        }
        else {
            if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Activate port C clock
            GPIOC->MODER &= ~(0b11 << (pins[i] - 10) * 2);
            GPIOC->MODER |= 0b11 << (pins[i] - 10) * 2; // Set ANALOG mode
        }
    }
    if(!(RCC->APB2ENR & (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8))
        RCC->APB2ENR |= (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8; // Activate ADC Clock

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

    // Configura o tamanho da sequência
    ADCx->SQR1 &= ~(0xF << 20); 
    ADCx->SQR1 |= ((sizePins - 1) << 20);

    // Configura o prescaler
    ADC->CCR &= ~(0b11 << 16);
    ADC->CCR |= (0b01 << 16);
    
    // Habilita o escaneamento de canais
    ADCx->CR1 |= ADC_CR1_SCAN;
    
    // Configura EOC ao final de cada conversão
    ADCx->CR2 |= ADC_CR2_EOCS;

    // Configura resolução
    ADCx->CR1 &= ~ADC_CR1_RES;
    ADCx->CR1 |= (resolution << 24);

    // Select the sample time
    for (uint8_t i = 0; i < sizePins; i++) 
    {
        if (pins[i] <= 9)
        {
            ADCx->SMPR2 &= ~(0b111 << (pins[i] * 3));
            ADCx->SMPR2 |=  (0b111 << (pins[i] * 3));
        }
        else
        {
            ADCx->SMPR1 &= ~(0b111 << ((pins[i] - 10) * 3));
            ADCx->SMPR1 |=  (0b111 << ((pins[i] - 10) * 3));
        }
    }

    ADCx->CR2 |= ADC_CR2_ADON;
    delay(1);    //aguarda o ADC iniciar

}

void adcSingleStart(ADC_TypeDef* ADCx, uint8_t pin, uint8_t resolution){
    if (pin < 8){
        if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port A clock
        GPIOA->MODER &= ~(0b11 << pin * 2);
        GPIOA->MODER |= 0b11 << pin * 2; // Set ANALOG mode
    }

    else if (pin == 8 || pin == 9){
        if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Activate port B clock
        GPIOA->MODER &= ~(0b11 << (pin - 8) * 2);
        GPIOA->MODER |= 0b11 << (pin - 8) * 2;
    }
    else {
        if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOCEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Activate port C clock
        GPIOA->MODER &= ~(0b11 << (pin - 10) * 2);
        GPIOA->MODER |= 0b11 << (pin - 10) * 2;
    }

    if(!(RCC->APB2ENR & (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8))
        RCC->APB2ENR |= (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8; // Activate ADC Clock

    ADCx->CCR |= (0b01 << 16); //prescaler /4 (84MHz/4 = 21MHz)

    ADCx->CR1 &= ~ADC_CR1_SCAN; //desabilita o escaneamento de canais
    ADC1->CR2 &= ~ADC_CR2_EOCS;

    ADCx->CR1 &= ~ADC_CR1_RES;      //limpa o campo da resolução
    ADCx->CR1 |= resolution << 24;  //escreve a resolução

    ADCx->SMPR2 |= 0b111; //seleção do tempo de amostragem (máximo)


    ADCx->SQR1 &= ~0xF << 20;   //seleciona a quantidade de canais (1 canal)
    ADCx->SQR3 &= ~0x1F;        //limpa o campo do canal
    ADCx->SQR3 |= pin;      //escreve o canal

    ADCx->CR2 |= ADC_CR2_ADON;
    Delay_ms(1);    //aguarda o ADC iniciar

}

uint16_t getAdcSingleConversion(ADC_TypeDef* ADCx){
    ADCx->CR2 |= ADC_CR2_SWSTART;
    while (!(ADCx->SR & ADC_SR_EOC));
    return ADCx->DR;
}

void getAdcMultiConversion(ADC_TypeDef* ADCx, uint16_t readPins[], uint8_t sizePins){
    // ADCx->CR2 |= ADC_CR2_SWSTART;
    // for (uint8_t i = 0; i < sizePins; i++){
    //     while(!(ADCx->SR & ADC_SR_EOC));
    //     readPins[i] = ADCx->DR;
    // }
    
    ADCx->CR2 |= ADC_CR2_SWSTART;
    for (uint8_t i = 0; i < sizePins; i++)
    {
        uint32_t timeout = 1000000;

        while (!(ADCx->SR & ADC_SR_EOC))
        {
            if (--timeout == 0)
            {
                printf("%d", i + 1);
            }
        }

        readPins[i] = ADCx->DR;
    }
}

void initAdcInterrupt(ADC_Typedef* ADCx, function func) {
    ADC1->CR2 |= ~ADC_CR2_EOCS;  //bit EOC setado ao final de cada sequencia de conversao
    ADCx->CR1 |= ADC_CR1_EOCIE;
    NVIC_EnableIRQ(ADC_IRQn);
    ADC_ISR[0] = func;
}

void getAdcInterruptConversion(ADC_Typedef* ADCx) {
    ADCx->CR2 |= ADC_CR2_SWSTART;
}

void adcTemperatureSensor(void){
    if(!(RCC->APB2ENR & RCC_APB2ENR_ADC1EN))
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;; // Activate ADC Clock

    ADC->CCR |= 0b01 << 16;
    ADC1->SQR1 &= ~(0xF << 20);
    ADC1->SQR3 &= ~(0x1F);
    ADC1->SQR3 |= 16;
    ADC1->SMPR1 |= (7 << 18);
    ADC->CCR |= ADC_CCR_TSVREFE;
    ADC1->CR2 |= ADC_CR2_ADON;
    delay(1);

}

float getTemperature(void) {
    uint32_t *p = (uint32_t *) 0x1FFF7A2C;
    uint32_t Word = *p;
    uint16_t TS_CAL1 = (Word & 0x0000FFFF);
    uint16_t TS_CAL2 = (Word & 0xFFFF0000) >> 16;

    ADC1->CR2 |= ADC_CR2_SWSTART;
    while(!(ADC1->SR & ADC_SR_EOC));
    uint32_t adcValue = ADC1->DR;
    return ((80.0f * (float) (adcValue - TS_CAL1)) / (TS_CAL2 - TS_CAL1)) + 30.0f;
}

int adcExternInterruptOn(ADC_TypeDef* ADCx){

//    adcStart(ADCx, pins, sizePins, resolution);
    ADCx->CR2 |= 0b01 << 28;
    ADCx->CR2 |= 0b1111 << 24;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[2] |= 0b0001 << 12; //PIN = PB11
    EXTI->RTSR |= 1 << 11;
    EXTI->EMR |= 1 << 1;

    if (ADC1->SR & ADC_SR_EOC) return ADCx->DR;
}

void watchdogAdc(ADC_TypeDef* ADCx, uint8_t pin, uint32_t highLimit, uint32_t lowLimit){
    ADCx->LTR = lowLimit;
    ADCx->HTR = highLimit;
    ADCx->CR1 |= ADC_CR1_AWDSGL;
    ADCx->CR1 &= ~ADC_CR1_AWDCH;
    ADCx->CR1 |= pin;
    ADCx->CR1 |= ADC_CR1_AWDEN;

    ADCx->CR1 |= ADC_CR1_AWDIE;
    NVIC_EnableIRQ(ADC_IRQn);

}

void getWatchdog(ADC_TypeDef* ADCx, function func){
    ADCx->CR2 |= ADC_CR2_SWSTART;
    ADC_ISR[0] = func;
}

void ADC_IRQHandler(void){
    if(ISR[0] == NULL) return;
        ADC_ISR[0]();
    ADC1->SR &= ~ADC_SR_AWD; // Reset the interruption flag;
    ADC2->SR &= ~ADC_SR_AWD;
}
