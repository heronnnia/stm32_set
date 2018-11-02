void EXTI2_IRQHandler()
{

}

void main()
{
	RCC_AHB1PeriphCLockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin = GPIO_Pin_2;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &gpio);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);

	EXTI_InitTypeDef exti;
	exti.EXTI_Line = EXTI_Line2;
	exti.EXTI_Mode = EXTI_Mode_Interrupt;
	exti.EXTI_Trigger = EXTI_Trigger_Rising;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);

	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = EXTI2_IRQn;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
	nvic.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&nvic);

	while(1);
}








