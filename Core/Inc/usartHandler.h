/**
 * @file usartHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 * @brief Handle with USART
 * @date 2026-09-17
 */

#ifndef USART_HANDLER_H
#define USART_HANDLER_H

#include "stm32f4xx_hal.h"

/**
 * @brief Send data by USART
 *
 * @param porta GPIO port to send
 * @param c Data to send
 */
void usartSend(USART_TypeDef* porta, char c);

/**
 * @brief Receive data by USART
 *
 * @param porta GPIO port to receive
 * @return char Data to get
 */
char usartGet(USART_TypeDef* porta);

#endif