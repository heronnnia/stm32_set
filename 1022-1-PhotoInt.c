/*
  문제 : LED가 상하로 왕복운동 하게 하시오. 
      단, 포토인터럽트에 물체가 끼이면 잠깐 중단했다가
      물체가 없으면 멈췄던 부위부터 다시 움직이게 하세요. 
*/

#define buzzer_pin GPIO_Pin_1
#define buzzer_port GPIOB
#define photo_port GPIOD
#define photo_pin GPIO_Pin_2

void main()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = buzzer_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(buzzer_port, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = photo_pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(photo_port, &GPIO_InitStructure);

	while(1)
	{
		if (GPIO_ReadInputDataBit(photo_port, photo_pin) == 1)
		{
			GPIO_SetBits(buzzer_port, buzzer_pin);
		} else
		{
			GPIO_ResetBits(buzzer_port, buzzer_pin);
		}
	}
}
