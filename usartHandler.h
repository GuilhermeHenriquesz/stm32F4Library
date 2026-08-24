#ifndef USART_HANDLER_H
#define USART_HANDLER_H

void usartSend(USART_TypeDef* porta, char c);

char usartGet(USART_TypeDef* porta);

#endif