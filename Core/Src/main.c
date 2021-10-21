//Programa para teste do conversor ADC (PA1 - ADC1)

#include "stm32f1xx.h"
#include "bib_STM32.h"
#include "bib_LCD.h"

float 		res;
char		texto[16];

int main(void){

	config_clock();

	RCC->APB2ENR |= (1<<2) | (1<<3);	//habilita clock dos GPIOs A e B

	GPIOA->CRL = 0x22220000;
	GPIOB->CRL = 0x02200000;

	inicializa_lcd4b();
	instrucao_lcd4b(128);				//linha superior do LCD
	imprime_lcd4b("Canal ADC1");

	ADC1->CR2 = 1;						//habilitar o conversor A/D
	ADC1->SMPR2 = 7<<3;					//239.5 ciclos do clock para cada conversao
	tempo_ms(2);

	while(1){
		ADC1->SQR3 = 1;					//prioridade na leitura do canal ADC1 (PA1)
		ADC1->CR2 = 1;					//inicia a conversao
		while((ADC1->SR & (1<<1))==0);	//aguarda terminar a conversao
		res = ADC1->DR;
		res = res / 4095;
		res = res * 3.3;
		sprintf(texto,"%4.2f V ",res);
		instrucao_lcd4b(192);			//linha inferior do LCD
		imprime_lcd4b(texto);
		tempo_ms(300);
	}
}
