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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = //GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
					GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	SysTick_Config(SystemCoreClock / 1000);
	GPIO_SetBits(GPIOB, GPIO_Pin_1); //해당비트는 1로
	Delay(1000);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1); //해당비트는 1로
	int i = 0, j = 0;

	int FndSeg[] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, // 4
					0b01101101, 0b01111101, 0b00100111, 0b01111111,  0b01101111}; // 9

	for(;;)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_All); //해당비트는 1로
		GPIO_ResetBits(GPIOC, 1 << i); //해당비트는 1로
		GPIO_ResetBits(GPIOC, FndSeg[j] << 8);

		i = (i+1) % 5;
		j = (j+1) % 10;

		Delay(1000);
	}
}


