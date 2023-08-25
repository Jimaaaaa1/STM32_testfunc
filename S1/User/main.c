#include "stm32f10x_conf.h"
#include "usart.h"
#include "Init.h"
#include "stdio.h"
#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "TIME.h"
#include <stdlib.h>
typedef unsigned long long u64;
char cmd = 0;
char cmd2 = 0;
int main()
{
	Serial_Init();
	sys_LED_Init();
	sys_USART_Init();
	printf("\n\n\n\n\n$RECOVER@");
	while(1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
		{
			Serial_SendString(USART1, "$START@");
			Delay_ms(50);
		}
	}
}

