#include "gpioHandler.h"

#define MS 1000

static uint8_t ports[11] = {0,0,0,0,0,0,0,0,0,0,0};

void delay(uint8_t ms){
	for(volatile uint8_t i = 0; i < ms*MS; i++);
}

void writeHigh(Pin* pin){
	pin->port->ODR |= 1 << pin->index;
}

void writeLow(Pin* pin){
	pin->port->ODR &= ~(1 << pin->index);
}

void togglePin(Pin* pin){
	pin->port->ODR ^= 1 << pin->index;
}

void virtualPwmWrite(Pin* pin, uint8_t value){
	writeHigh(pin);
	for(uint8_t i = 0; i < value*MS/10; i++);
	writeLow(pin);
	for(uint8_t i = 0; i < (100 - value)*MS/10; i++);
}

void pinStart(Pin *pin, GPIO_TypeDef* port, uint8_t index, uint8_t mode){
	index = ((uint32_t)port - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);

	if(ports[index] != 1) {
		RCC->AHB1ENR |= 1 << index; //Activate port clock
		ports[index] = 1;
	}

	port->MODER &= ~(0b11<<index);
	port->MODER |= mode<<index;

	pin->port = port;
	pin->index = index;
}

void setPullDown(Pin* pin){
	pin->port->PUPDR &= ~(1 << pin->index*2);
	pin->port->PUPDR |= 0b10 << pin->index*2;
}

void setPullUp(Pin* pin){
	pin->port->PUPDR &= ~(0b10 << pin->index*2);
	pin->port->PUPDR |= 1 << pin->index*2;
}

uint8_t readPin(Pin* pin) {
	if(((pin->port->IDR) & (1 << pin->index)) != 0)
		return 1;
	else return 0;
}
