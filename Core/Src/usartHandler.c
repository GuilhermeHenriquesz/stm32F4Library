#include "usartHandler.h"

void usartSend(USART_TypeDef* porta, char c){
    porta->DR = c;
    while (!(porta->SR & USART_SR_TXE));
}

char usartGet(USART_TypeDef* porta){
    return porta->DR;
}