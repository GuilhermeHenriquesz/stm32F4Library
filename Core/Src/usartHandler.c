#include "usartHandler.h"

void usartSend(USART_TypeDef* porta, char c){
    porta->DR = c;
    while (!(porta->SR & USART_SR_TXE));
}

char usartGet(USART_TypeDef* porta){
    return porta->DR;
}

void usartInit(){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = 84;
	USART1->CR1 |= (USART_CR1_TE | USART_CR1_UE);
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (0b10 << 20) | (0b10 << 18);
	GPIOA->AFR[1] |= (0b0111 << 8) | (0b0111 << 4);
}