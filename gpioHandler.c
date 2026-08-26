#include "gpioHandler.h"

#define MS 1000

void delay(int ms){
	for(int i = 0; i < ms*MS; i++);
}

void writeHigh(Pin* pin){
	pin->porta->ODR |= 1 << pin->pino;
}

void writeLow(Pin* pin){
	pin->porta->ODR &= ~(1 << pin->pino);
}

void togglePin(Pin* pin){
	pin->porta->ODR ^= 1 << pin->pino;
}

void virtualPwmWrite(Pin* pin, int value){
	writeHigh(pin);
	for(int i = 0; i < value*MS/10; i++);
	writeLow(pin);
	for(int i = 0; i < (100 - value)*MS/10; i++);
}

void pinStart(Pin *pin, GPIO_TypeDef* porta, int pino){
	pin->porta = porta;
	pin->pino = pino;
}

void setPullDown(Pin* pin){
	pin->porta->PUPDR &= ~(1 << pin*2);
	pin->porta->PUPDR |= 0b10 << pin*2;
}

void setPullUp(Pin* pin){
	pin->porta->PUPDR &= ~(0b10 << pin*2);
	pin->porta->PUPDR |= 1 << pin*2;
}

int readPin(Pin* pin) {
	if(((pin->porta->IDR) & (1 << pin->pino)) != 0)
		return 1;
	else return 0;
}
