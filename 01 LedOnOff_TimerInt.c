/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"

int mstime = 0;
void SysTick_Handler()
{
	mstime++;
}

void Delay(int ms)
{
	int future=mstime + ms;
	while (future > mstime);
}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = //GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
					GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	SysTick_Config(SystemCoreClock / 1000);

	for(;;)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_All); //해당비트는 1로
		Delay(1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_All); //해당비트는 1로
		Delay(1000);
	}
}
