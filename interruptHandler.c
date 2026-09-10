#include "interruptHandler.h"

void interruptiOn(void){
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

void interruptPin(GPIO_TypeDef* porta, uint8_t line, uint8_t edge){
    uint8_t index = line / 4;
    uint8_t shift = (line % 4) * 4;
    uint8_t port = ((uint32_t)porta - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);

    SYSCFG->EXTICR[index] |= (port<<shift);

    switch edge{
        case 0:
            EXTI->FTSR |= 1 << line;
            break;
        case 1:
            EXTI->RTSR |= 1 << line;
            break;
        case 2:
            EXTI->FTSR |= 1 << line;
            EXTI->RTSR |= 1 << line;
    }
    
    EXTI->IMR |= 1 << line;
}