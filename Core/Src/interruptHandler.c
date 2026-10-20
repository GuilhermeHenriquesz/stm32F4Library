#include <stdlib.h>
#include "interruptHandler.h"

void interruptiOn(void){
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

void interruptPin(Pin* pin, uint8_t edge, uint8_t priority, function func){
    uint8_t index = pin->index / 4;
    uint8_t shift = (pin->index % 4) * 4;
    uint8_t port = ((uint32_t)(pin->port) - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);

    SYSCFG->EXTICR[index] |= (port<<shift);

    switch (edge){
        case 0:
            EXTI->FTSR |= 1 << pin->index;
            break;
        case 1:
            EXTI->RTSR |= 1 << pin->index;
            break;
        case 2:
            EXTI->FTSR |= 1 << pin->index;
            EXTI->RTSR |= 1 << pin->index;
    }

    EXTI->IMR |= 1 << pin->index;
    
    if (pin->index < 5){
        switch (pin->index){
            case 0:
                NVIC_SetPriority(EXTI0_IRQn, priority);
                NVIC_EnableIRQ(EXTI0_IRQn);
                ISRs[0] = func;
                break;
            case 1:
                NVIC_SetPriority(EXTI1_IRQn, priority);
                NVIC_EnableIRQ(EXTI1_IRQn);
                ISRs[1] = func;
                break;
            case 2:
                NVIC_SetPriority(EXTI2_IRQn, priority);
                NVIC_EnableIRQ(EXTI2_IRQn);
                ISRs[2] = func;
                break;
            case 3:
                NVIC_SetPriority(EXTI3_IRQn, priority);
                NVIC_EnableIRQ(EXTI3_IRQn);
                ISRs[3] = func;
                break;
            case 4:
                NVIC_SetPriority(EXTI4_IRQn, priority);
                NVIC_EnableIRQ(EXTI4_IRQn);
                ISRs[4] = func;
        }
    }
    else if (pin->index < 10){
        NVIC_SetPriority(EXTI9_5_IRQn, priority);
        NVIC_EnableIRQ(EXTI9_5_IRQn);
        ISRs[5] = func;
    }
    else{
        NVIC_SetPriority(EXTI15_10_IRQn, priority);
        NVIC_EnableIRQ(EXTI15_10_IRQn);
        ISRs[6] = func;
    }
}

void EXTI0_IRQHandler(void){
    if (!(EXTI->PR & EXTI_PR_PR0)) return;
    
    EXTI->PR = EXTI_PR_PR0;

    if(ISRs[0] == NULL) return;
    ISRs[0]();
}

void EXTI1_IRQHandler(void){
    if (!(EXTI->PR & EXTI_PR_PR1)) return;
    
    EXTI->PR = EXTI_PR_PR1;

    if(ISRs[1] == NULL) return;
    ISRs[1]();
}

void EXTI2_IRQHandler(void){
    if (!(EXTI->PR & EXTI_PR_PR2)) return;
    
    EXTI->PR = EXTI_PR_PR2;

    if(ISRs[2] == NULL) return;
    ISRs[2]();
}

void EXTI3_IRQHandler(void){
    if (!(EXTI->PR & EXTI_PR_PR3)) return;
    
    EXTI->PR = EXTI_PR_PR3;

    if(ISRs[3] == NULL) return;
    ISRs[3]();
}

void EXTI4_IRQHandler(void){
    if (!(EXTI->PR & EXTI_PR_PR4)) return;
    
    EXTI->PR = EXTI_PR_PR4;

    if(ISRs[4] == NULL) return;
    ISRs[4]();
}

void EXTI9_5_IRQHandler(void){
    if(ISRs[5] == NULL) return;
    ISRs[5]();
}

void EXTI15_10_IRQHandler(void){
    if(ISRs[6] == NULL) return;
    ISRs[6]();
}