#include "stm32f4xx.h"

void EXT_Init(void);
void configureLED(void);
void External_Interrupt_Enable(void);


void EXT_Init(void)
{

//1. Enable TIM@ and GPIO clock
	RCC->APB1ENR |= (1<<0);  // enable PORTA clock
	EXTI->RTSR |=(1<<0);     // enable rising edge trigger
	EXTI->IMR |=(1<<0);      // disable the interrupt mask
}
void configureLED(void)
{
	RCC->AHB1ENR |=(1UL<<3);  //Enable GPIOD clock
	GPIOD->MODER &= ~(0xFFUL<<12*2);
	GPIOD->MODER |= (0x55UL<<12*2);    //configure pins PD12-15 as output
}
void External_Interrupt_Enable(void)
{
	NVIC->ISER[0] |= 1<<6;    //enable external interrupt line

}
int main ()
{

	EXT_Init();
	configureLED();
	External_Interrupt_Enable();
	while(1)
	{

}
}
void EXTI0_IRQHandler( )
{
	GPIOD->ODR ^= (0xFUL<<12);
	EXTI->PR |= (1<<0);          //clear the interrupt flag

}


