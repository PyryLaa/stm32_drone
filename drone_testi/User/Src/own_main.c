#include "own_main.h"
#include "stm32f407xx.h"

void own_main(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	GPIOD->MODER = 0x55000000;

	while(1){
		GPIOD->ODR = 0xF000;
		HAL_Delay(500);
		GPIOD->ODR = 0;
		HAL_Delay(500);
	}
}
