#include "bibDosBacana.h"

void writeHigh(Pin* pin){
	pin->porta->ODR |= 1 << pin->pino;
}

void writeLow(Pin* pin){
	pin->porta->ODR &= ~(1 << pin->pino);
}

void pinStart(Pin **pin, GPIO_TypeDef* porta, int pino){
	*pin = malloc(sizeof(Pin));
	(*pin)->porta = porta;
	(*pin)->pino = pino;
}

int readPin(Pin* pin) {
	if(((pin->porta->IDR) & (1 << pin->pino)) != 0)
		return 1;
	else return 0;
}
