#include "usart.h"
#include "Delay.h"
#include "LED.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>


u8 RxBuffer[100]={0};              /* USART1 Using  */
u8 RxCnt = 0;
u8 input_string[100];
//u8 charNum=0;
//int exectime=0;
//u8 led[4] = {0};

void System_Reset(void) {
	__set_FAULTMASK(1); //关闭所有中断
	NVIC_SystemReset(); //进行软件复位
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    RxBuffer[RxCnt++] = USART_ReceiveData(USART1);
		if(RxCnt > 2)
		{
			extern char cmd,cmd2;
			char flag_head, flag_tail;
			for(uint8_t i = 0; i<RxCnt; i++)
			{
				if(RxBuffer[i] == '$')  //head
				{
					flag_head = i;
				}
				if(RxBuffer[i] == '@') //tail
				{
					flag_tail = i;
					cmd = RxBuffer[flag_head + 3];
					cmd2 = RxBuffer[flag_head + 4];
					strncpy(input_string, RxBuffer+flag_head+1, flag_tail - flag_head - 1);
					input_string[flag_tail-flag_head-1] = 0;
					
					if( cmd >='1' && cmd <='9' && cmd2 >='1' && cmd2 <='9')
						{
							Gpio_set_bit_case(cmd);
							Gpio_set_bit_case(cmd2);
							Delay_ms(50);
							Gpio_reset_bit_case(cmd);
							Gpio_reset_bit_case(cmd2);
						}
					else if(strcmp(input_string,"RESET")==0)
						{
							System_Reset();
						}
					else
						{
							printf("%s is the wrong input", input_string);
						}
					RxCnt = 0;			
					break;
				}
			}
		}
  }
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void Serial_SendByte(USART_TypeDef* pUSARTx, uint8_t Byte)
{
	USART_SendData(pUSARTx, Byte);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Serial_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t Data)
{
	uint8_t temp_h,temp_l;
	temp_h = (Data&0xff00) >> 8;
	temp_l = (Data&0x00ff);
	
	USART_SendData(pUSARTx, temp_h);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(pUSARTx, temp_l);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(USART_TypeDef* pUSARTx, uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(pUSARTx, Array[i]);
	}
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

void Serial_SendString(USART_TypeDef* pUSARTx, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(pUSARTx,String[i]);
	}
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(DEFAULT_USART,ch);
	while (USART_GetFlagStatus(DEFAULT_USART, USART_FLAG_TXE) == RESET);
	return ch;
}

void Serial_Printf(USART_TypeDef* pUSARTx, char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(pUSARTx, String);
}

void Gpio_set_bit_case(char out_io)
{
	int out_io_int = out_io - '0';
	switch(out_io_int)
	{
		case 2:
			{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
//			printf("out_2 ");
			break;
			}
		case 3: 
			{
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
//			printf("out_3 ");
			break;
			}				
		case 4:
			{
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
//			printf("out_4 ");
			break;
			}	
		case 5:
			{
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
//			printf("out_5 ");
			break;
			}	
	}
}

void Gpio_reset_bit_case(char out_io)
{
	int out_io_int = out_io - '0';
	switch(out_io_int)
	{
		case 2:
			{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			break;
			}
		case 3:
			{
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			break;
			}
		case 4:
			{
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			break;
			}
		case 5:
			{
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
			}
	}
}

