#include <stdlib.h>
#include "interruptHandler.h"

void interruptiOn(void){
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

void interruptPin(Pin* pin, uint8_t edge, uint8_t priority, function func){
    uint8_t index = pin->pino / 4;
    uint8_t shift = (pin->pino % 4) * 4;
    uint8_t port = ((uint32_t)(pin->porta) - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);

    SYSCFG->EXTICR[index] |= (port<<shift);

    switch edge{
        case 0:
            EXTI->FTSR |= 1 << pin->pino;
            break;
        case 1:
            EXTI->RTSR |= 1 << pin->pino;
            break;
        case 2:
            EXTI->FTSR |= 1 << pin->pino;
            EXTI->RTSR |= 1 << pin->pino;
    }

    EXTI->IMR |= 1 << pin->pino;
    
    if (port < 5){
        switch port{
            case 0:
                NVIC_SetPriority(EXTI0_IRQn, priority);
                NVIC_EnableIRQ(EXTI0_IRQn);
                ISR[0] = func;
                break;
            case 1:
                NVIC_SetPriority(EXTI1_IRQn, priority);
                NVIC_EnableIRQ(EXTI1_IRQn);
                ISR[1] = func;
                break;
            case 2:
                NVIC_SetPriority(EXTI2_IRQn, priority);
                NVIC_EnableIRQ(EXTI2_IRQn);
                ISR[2] = func;
                break;
            case 3:
                NVIC_SetPriority(EXTI3_IRQn, priority);
                NVIC_EnableIRQ(EXTI3_IRQn);
                ISR[3] = func;
                break;
            case 4:
                NVIC_SetPriority(EXTI4_IRQn, priority);
                NVIC_EnableIRQ(EXTI4_IRQn);
                ISR[4] = func;
        }
    }
    else if (port < 10)
        NVIC_SetPriority(EXTI9_5_IRQn, priority);
        NVIC_EnableIRQ(EXTI9_5_IRQn);
        ISR[5] = func;
    else
        NVIC_SetPriority(EXTI15_10_IRQn, priority);
        NVIC_EnableIRQ(EXTI15_10_IRQn);
        ISR[6] = func;
}

void EXTI0_IRQHanlder(void){
    if (!(EXTI->PR & EXTI_PR_PR0)) return;
    
    EXTI->PR = EXTI_PR_PR0;

    if(ISR[0] == NULL) return;
    ISR[0]();
}

void EXTI1_IRQHanlder(void){
    if (!(EXTI->PR & EXTI_PR_PR1)) return;
    
    EXTI->PR = EXTI_PR_PR1;

    if(ISR[1] == NULL) return;
    ISR[1]();
}

void EXTI2_IRQHanlder(void){
    if (!(EXTI->PR & EXTI_PR_PR2)) return;
    
    EXTI->PR = EXTI_PR_PR2;

    if(ISR[2] == NULL) return;
    ISR[2]();
}

void EXTI3_IRQHanlder(void){
    if (!(EXTI->PR & EXTI_PR_PR3)) return;
    
    EXTI->PR = EXTI_PR_PR3;

    if(ISR[3] == NULL) return;
    ISR[3]();
}

void EXTI4_IRQHanlder(void){
    if (!(EXTI->PR & EXTI_PR_PR4)) return;
    
    EXTI->PR = EXTI_PR_PR4;

    if(ISR[4] == NULL) return;
    ISR[4]();
}

void EXTI9_5_IRQHanlder(void){
    if(ISR[5] == NULL) return;
    ISR[5]();
}

void EXTI15_10_IRQHanlder(void){
    if(ISR[6] == NULL) return;
    ISR[6]();
}