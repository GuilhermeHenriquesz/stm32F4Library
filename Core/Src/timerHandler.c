#include "timerHandler.h"

void delayInit(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = 83;
	TIM2->EGR = TIM_EGR_UG;
	TIM2->CR1 |= TIM_CR1_CEN;
    isInitiated = 1;
}

void delay(uint32_t ms){
    if(!isInitiated) delayInit();
    TIM2->CNT = 0;
	while(TIM2->CNT < ms*1000);
}

void microDelay(uint32_t microSeconds){
    if(!isInitiated) delayInit();
    TIM2->CNT = 0;
	while(TIM2->CNT < microSeconds);
}

void sysTick(uint32_t reloadValue, function func) {
    SysTick->LOAD = reloadValue - 1;
    SysTick->CTRL = 0b011;
    ISRs[0] = func;

}

void timerStart(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm) {
    if (TIM2 <= TIMx && TIMx <= TIM5) RCC->APB1ENR |= (1 << ((uint32_t)TIMx - (TIM2_BASE)) / ((TIM3_BASE) - (TIM2_BASE)));
    TIMx->PSC = prescaler - 1;
    TIMx->EGR |= TIM_EGR_UG;
    TIMx->ARR |= reload - 1;
    TIMx->CR1 &= ~(0b11 << 5);
    TIMx->CR1 &= ~(0b11 << 4);
    if (countForm == 2) TIMx->CR1 |= 0b01 << 5;
    else TIMx->CR1 |= countForm << 4;


    TIMx->CR1 |= TIM_CR1_CEN;
}

void timerInterruption(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm, function func){
    if (TIM2 <= TIMx && TIMx <= TIM5) RCC->APB1ENR |= (1 << ((uint32_t)TIMx - (TIM2_BASE)) / ((TIM3_BASE) - (TIM2_BASE))); // ATENCAO TESTAR SE FUNCIONA A ABILITACAO DO CLOCK
    TIMx->PSC = prescaler - 1;
    TIMx->EGR |= TIM_EGR_UG;
    TIMx->ARR |= reload - 1;
    TIMx->CR1 &= ~(0b11 << 5);
    TIMx->CR1 &= ~(0b11 << 4);
    if (countForm == 2) TIMx->CR1 |= 0b01 << 5;
    else TIMx->CR1 |= countForm << 4;

    TIMx->DIER |= TIM_DIER_UIE;

    switch (TIMx){
        case (TIM2):
            NVIC_EnableIRQ(TIM2_IRQn);
            ISRs[1] = func;
            break;
        case (TIM3):
            NVIC_EnableIRQ(TIM3_IRQn);
            ISRs[2] = func;
            break;
        case (TIM4):
            NVIC_EnableIRQ(TIM4_IRQn);
            ISRs[3] = func;
            break;
        case (TIM5):
            NVIC_EnableIRQ(TIM5_IRQn);
            ISRs[4] = func;
            break;
    }

    TIMx->CR1 |= TIM_CR1_CEN;
}

void timerPWM(TIM_TypeDef* TIMx, uint16_t prescaler, uint32_t reload, uint8_t countForm) {
    if (TIM2 <= TIMx && TIMx <= TIM5) RCC->APB1ENR |= (1 << ((uint32_t)TIMx - (TIM2_BASE)) / ((TIM3_BASE) - (TIM2_BASE)));
    TIMx->PSC = prescaler - 1;

    TIMx->ARR |= reload - 1;
    TIMx->CR1 &= ~(0b11 << 5);
    TIMx->CR1 &= ~(0b11 << 4);

    TIMx->CCMR2 |= 0b110 << 4; //PWM MODO 1
    TIMx->CCMR2 |= TIM_CCMR2_OC3PE;
    TIMx->CCER |= TIM_CCER_CC3E;
    TIMx->EGR |= TIM_EGR_UG;

    if (countForm == 2) TIMx->CR1 |= 0b01 << 5;
    else TIMx->CR1 |= countForm << 4;

    TIMx->CR1 |= TIM_CR1_CEN;
}

uint32_t getTimer(TIM_TypeDef* TIMx){
    return TIMx->CNT;
}

void resetTimer(TIM_TypeDef* TIMx){
    TIMx->CNT = 0;
}

void SysTick_Handler(){
    if(ISRs[0] == NULL) return;
        ISRs[0]();
}

void TIM2_IRQHandler(){
    TIM2->SR &= ~TIM_SR_UIF;
    ISRs[1]();
}

void TIM3_IRQHandler(){
    TIM3->SR &= ~TIM_SR_UIF;
    ISRs[2]();
}

void TIM4_IRQHandler(){
    TIM4->SR &= ~TIM_SR_UIF;
    ISRs[3]();
}

void TIM5_IRQHandler(){
    TIM5->SR &= ~TIM_SR_UIF;
    ISRs[4]();
}
