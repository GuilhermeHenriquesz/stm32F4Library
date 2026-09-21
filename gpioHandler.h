/**
 * @file gpioHandler.h
 * @authors Fabio Henrique and Guilherme Henriques
 *
 * @brief Handle with GPIO
 *
 * @date 2026-09-17
 */

#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include "stm32f4xx_hal.h"
#include <stdlib.h>

/**
 * @brief Abstract pins of GPIOs
 * @details A struct that contains the port and the pin index
 */

typedef struct pin{
	GPIO_TypeDef* port; /**< GPIO port */
	uint8_t index; /**< Pin index */
}Pin;

/**
 * @brief Enumerate pin modes to provide more code understandment
 * @details In the stms registers, the bits that defines the GPIO pin operation is 0b00, 0b01, 0b10 and 0b11, or just 0, 1, 2 and 3
 */
enum{
	INPUT,
	OUTPUT,
	ALTERNATE,
	ANALOG
}

/**
 * @brief Write high state in a output pin
 *
 * @param pin Pin to be written
 */
void writeHigh(Pin* pin);

/**
 * @brief Write low state in a output pin
 *
 * @param pin Pin to be written
 */
void writeLow(Pin* pin);

/**
 * @brief Alternate the state in a output pin
 * 
 * @param pin Pin to be alternated
 */
void togglePin(Pin* pin);

/**
 * @brief Get the status of a output pin
 *
 * @param pin Pin to be read
 * @return A uint_8 that indicates if the state is high(1) or low(0)
 */
uint8_t getPinStatus(Pin* pin);

/**
 * @brief Write a pwm in software in a gpio pin
 * @warning This function just work to a specific context, call this function and, after it, call another delay will break completely the logic of pwm
 *
 * @param pin Pin to be written
 * @param value Percentage of PWM value -> 0 to 100
 */
void virtualPwmWrite(Pin* pin, uint8_t value);

/**
 * @brief Start the struct pin, set the mode of the pin and enable the pin port clock
 *
 * @param[out] pin Pin to be started
 * @param[out] port Pins port
 * @param[in] index Pins index
 * @param[in] mode Pins mode
 */
void pinStart(Pin *pin, GPIO_TypeDef* port, uint8_t index, uint8_t mode);

/**
 * @brief Set pull down resistor to a input pin
 *
 * @param pin Pin to be setted
 */
void setPullDown(Pin* pin);

/**
 * @brief Set pull up resistor to a input pin
 *
 * @param pin Pin to be setted
 */
void setPullUp(Pin* pin);

/**
 * @brief Read a input pin
 *
 * @param pin Pin to be read
 * @return A uint_8 that indicates if the pin is high(1) or low(0)
 */
uint8_t readPin(Pin* pin);

#endif