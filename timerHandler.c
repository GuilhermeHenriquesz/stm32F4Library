#include "timerHandler.h"

void timerInit(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 83;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->CR1 |= TIM_CR1_CEN;
    isInitiated = 1;
}

void delay(uint32_t ms){
    if(!isInitiated) timerInit();
    TIM2->CNT = 0;
	while(TIM2->CNT < delay*1000);
}

void microDelay(uint32_t microSeconds){
    if(!isInitiated) timerInit();
    TIM2->CNT = 0;
	while(TIM2->CNT < delay);
}