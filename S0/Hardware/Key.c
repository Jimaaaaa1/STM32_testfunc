#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "usart.h"
#include "Key.h"


void KEY_EXTI_Config(void)
{
		GPIO_InitTypeDef GPIOB_struct;	
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
		

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
		GPIOB_struct.GPIO_Mode = GPIO_Mode_IPU;
		GPIOB_struct.GPIO_Pin = GPIO_Pin_1;
		GPIOB_struct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIOB_struct);
 
    EXTI_InitStruct.EXTI_Line       =   EXTI_Line1;    
    EXTI_InitStruct.EXTI_LineCmd    =   ENABLE;        
    EXTI_InitStruct.EXTI_Mode       =   EXTI_Mode_Interrupt;    
    EXTI_InitStruct.EXTI_Trigger    =   EXTI_Trigger_Falling;   
    EXTI_Init(&EXTI_InitStruct);  
 
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);  
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
    
    NVIC_InitStruct.NVIC_IRQChannel     =   EXTI1_IRQn;         
    NVIC_InitStruct.NVIC_IRQChannelCmd  =   ENABLE;             
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority   =   1; 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority          =   0;
    NVIC_Init(&NVIC_InitStruct);        
}


void EXTI1_IRQHandler(void)
{	
	
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		Delay_ms(50);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		printf("A5 is on");
	}	
	EXTI_ClearITPendingBit(EXTI_Line1);
	while(EXTI_GetITStatus(EXTI_Line1) != RESET);
}