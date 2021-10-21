//funcoes basicas para o STM32

#include "stm32f1xx.h"
#include "bib_STM32.h"

void	config_clock(void){
	RCC->CR |= (1<<16);
	while (!RCC_CR_HSERDY);
	RCC -> CFGR = 0x001D0402;
	RCC -> CR |= (1<<24);
	while (!RCC_CR_PLLRDY);
	FLASH -> ACR = 0x12;
}

void	tempo_ms(uint16_t valor){
	for(uint16_t a=1;a<=valor;a++){
		//SysTick -> LOAD = 71999;							//valor de 1 ms conisderando 72 MHz
		SysTick -> LOAD = 8999;								//valor de 1 ms considerando 9 MHz
		SysTick -> CTRL = 0x01;
		while ((SysTick -> CTRL & 0x10000)==0);
		SysTick -> CTRL = 0;
	}
}
