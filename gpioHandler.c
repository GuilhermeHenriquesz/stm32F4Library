#include "gpioHandler.h"

#define MS 10000

static uint8_t ports[11] = {0,0,0,0,0,0,0,0,0,0,0};

void writeHigh(Pin* pin){
	pin->port->ODR |= 1 << pin->index;
}

void writeLow(Pin* pin){
	pin->port->ODR &= ~(1 << pin->index);
}

void togglePin(Pin* pin){
	pin->port->ODR ^= 1 << pin->index;
}

uint8_t getPinStatus(Pin* pin){
	uint32_t pinStatus = 1 << pin->index;
	pinStatus &= pin->port->ODR;
	if(!pinStatus) return 0;
	return 1;
}

void virtualPwmWrite(Pin* pin, uint8_t value){
	writeHigh(pin);
	for(uint8_t i = 0; i < value*MS/10; i++);
	writeLow(pin);
	for(uint8_t i = 0; i < (100 - value)*MS/10; i++);
}

void pinStart(Pin *pin, GPIO_TypeDef* port, uint8_t index, uint8_t mode){
	uint8_t indexPort = ((uint32_t)port - GPIOA_BASE) / (GPIOB_BASE - GPIOA_BASE);

	if(ports[indexPort] != 1) {
		RCC->AHB1ENR |= 1 << indexPort; //Activate port clock
		ports[indexPort] = 1;
	}

	port->MODER &= ~(0b11<<index * 2);
	port->MODER |= mode<<index * 2;

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
