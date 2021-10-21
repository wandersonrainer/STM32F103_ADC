//biblioteca de interface com LCD caractere

#include "stm32f1xx.h"

void	inicializa_lcd4b(void){
	tempo_ms(100);
	instrucao_lcd4b(0x02);	//return home
	instrucao_lcd4b(0x2C);	//function set (4 bits)
	instrucao_lcd4b(0x06);	//entry mode set
	instrucao_lcd4b(0x0C);	//display on/off control
	instrucao_lcd4b(0x01);	//clear display
}

void	imprime_lcd4b(char palavra[]){
	int indice = 0;
	int tam = strlen(palavra);	//STRING LENGTH
	while(indice<tam){
		dado_lcd4b(palavra[indice]);
		indice++;
	}
}

void	instrucao_lcd4b(uint16_t inst){
	GPIOB->ODR &= ~(1<<5);		//PB5 (RS) = 0: instrucao
	GPIOA->ODR = inst;			//bits 7 a 4
	GPIOB->ODR |= (1<<6);		//PB6 (EN) = 1
	tempo_ms(1);
	GPIOB->ODR &= ~(1<<6);		//PB6 (EN) = 0
	tempo_ms(1);
	GPIOA->ODR = inst<<4;		//bits 3 a 0
	GPIOB->ODR |= (1<<6);		//PB6 (EN) = 1
	tempo_ms(1);
	GPIOB->ODR &= ~(1<<6);		//PB6 (EN) = 0
	tempo_ms(1);
}

void	dado_lcd4b(uint16_t dado){
	GPIOB->ODR |= (1<<5);		//PB5 (RS) = 1: dado
	GPIOA->ODR = dado;			//bits 7 a 4
	GPIOB->ODR |= (1<<6);		//PB6 (EN) = 1
	tempo_ms(1);
	GPIOB->ODR &= ~(1<<6);		//PB6 (EN) = 0
	tempo_ms(1);
	GPIOA->ODR = dado<<4;		//bits 3 a 0
	GPIOB->ODR |= (1<<6);		//PB6 (EN) = 1
	tempo_ms(1);
	GPIOB->ODR &= ~(1<<6);		//PB6 (EN) = 0
	tempo_ms(1);
}
