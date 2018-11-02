
#define KM_INT_1 0b00010001
#define KM_INT_2 0b00010010
#define KM_INT_3 0b00010100
#define KM_INT_4 0b00011000
#define KM_INT_5 0b00100001

void matrix_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_Initstruct;
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Initstruct.GPIO_OType = GPIO_OType_PP;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Initstruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_Initstruct);
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Initstruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_Initstruct);
}

void simple_delay(int count)
{
	int i;
	for(i=0; i<count; i++);
}

int prevKey = 0;
int GetKey()
{
	int i;
	for(i=0; i<4; i++)
	{
		GPIO_ResetBits(GPIOA, 0b1111 << 8);
		GPIO_SetBits(GPIOA, 1 << i << 8);
		simple_delay(30);
		int key = (GPIO_ReadInputData(GPIOA) >> 4) & 0b1111;
		if (key != 0)
		{
			int ret = 1 << 4 << i | key;

			if (ret != prevKey)
			{
				prevKey = ret;
				return ret;
			}
			else
				return 0;
		}
	}
	prevKey = 0;
	return 0;
}
