

void dacStart(uint8_t pin, uint8_t resolution) {
    if(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOAEN)) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Activate port clock

    if(!(RCC->APB1ENR & RCC_APB1ENR_DACEN)) RCC->AHB1ENR |= RCC_APB1ENR_DACEN; // Activate DAC clock

    DAC->CR |= (1U << (pin * 16U)); // Activate the selectioned pin (PA4 or PA5)

    GPIOA->MODER &= ~(0b11 << (pin + 4) * 2);
    GPIOA->MODER |= 0b11 << (pin + 4) * 2;





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

