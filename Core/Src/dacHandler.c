

void dacStart(uint8_t pin, uint8_t resolution) {
    if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port A clock

    if(!(RCC->APB1ENR & RCC_APB1ENR_DACEN)) RCC->AHB1ENR |= RCC_APB1ENR_DACEN; // Activate DAC clock

    GPIOA->MODER &= ~(0b11 << (pin + 4) * 2);
    GPIOA->MODER |= 0b11 << (pin + 4) * 2; // Set ANALOG mode

    DAC->CR |= (1U << (pin * 16U)); // Activate the selectioned pin (PA4 or PA5)
}

void dacStart2(uint8_t pin, uint8_t resolution, uint8_t waveform, uint8_t amplitude){

    if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port A clock

    if(!(RCC->APB1ENR & RCC_APB1ENR_DACEN)) RCC->AHB1ENR |= RCC_APB1ENR_DACEN; // Activate DAC clock

    GPIOA->MODER &= ~(0b11 << (pin + 4) * 2);
    GPIOA->MODER |= 0b11 << (pin + 4) * 2; // Set ANALOG mode

    DAC->CR |= (2-waveform) << (6 + 16*pin);    // Select the waveform
    DAC->CR |= amplitude << (8 + 16*pin);       // Select the amplitude
    DAC->CR |= 0b111 << (3 + 16*pin);           // Select the software trigger
    DAC->CR |= 1 << (2 + 16*pin);               // Enable the trigger
    DAC->CR |= 1 << 16*pin;                     // Enable the channel

    DAC->CR |= (1U << (pin * 16U)); // Activate the selectioned pin (PA4 or PA5)





}

void dacSetValue(uint8_t pin, uint8_t resolution, uint16_t value){
    if (pin){
       switch(resolution) {
       case (0):
           DAC->DHR8R1 = value;
           break;
       case (1):
           DAC->DHR12L1 = value;
           break;
       case (2):
          DAC->DHR12R1 = value;
          break;
       }
    }else {
        switch(resolution) {
        case (0):
           DAC->DHR8R2 = value;
           break;
        case (1):
           DAC->DHR12L2 = value;
           break;
        case (2):
          DAC->DHR12R2 = value;
          break;
        }
    }
}

void dacTrigger(uint8_t pin){
    DAC->SWTRIGR |= 1 << pin;

}

