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
int in_2, in_3,in_4, in_5, in_all;
int main()
{
	Serial_Init();
	sys_LED_Init();
	sys_USART_Init();
	KEY_EXTI_Config();
	while(1)
	{
		
		in_2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)){printf("2");}
		in_3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)){printf("3");}
		in_4 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)){printf("4");}
		in_5 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)){printf("5");}
		in_all = in_2 + in_3 + in_4 + in_5;
		if (in_all == 2)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
			Delay_ms(50);
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
//			printf("start signal is send");
		}
//		printf("\n");
	}
}

