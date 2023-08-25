#include "stm32f10x.h"

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t xus)
{
	SysTick->LOAD = 72 * xus;				//设置定时器重装值
	SysTick->VAL = 0x00;					//清空当前计数值
	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
	SysTick->CTRL = 0x00000004;				//关闭定时器
}

/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 


//#include "stm32f10x.h"



//static u8 delaying_times = 0;//该次delay是否为中断中的第二次进入
//static u16 delaying_finish = 0;//在进入该次delay时上次是否已经完成延时


///**
//  * @brief  微秒级延时
//  * @param  xus 延时时长，范围：0~233015
//  * @retval 无
//  */
//void Delay_us(uint32_t xus)
//{
//	SysTick->LOAD = 72 * xus;				//设置定时器重装值
//	SysTick->VAL = 0x00;					//清空当前计数值
//	SysTick->CTRL = 0x00000005;				//设置时钟源为HCLK，启动定时器
//	while(!(SysTick->CTRL & 0x00010000));	//等待计数到0
//	SysTick->CTRL = 0x00000004;				//关闭定时器
//}

///**
//  * @brief  毫秒级延时
//  * @param  xms 延时时长，范围：0~4294967295
//  * @retval 无
//  */
//void Delay_ms(uint32_t xms)
//{
//	u32 last_systick_val;
//	if(delaying_times != 0)//如果主程序在跑delay函数的过程中，发生中断并在中断中又进入了delay函数
//	{
//		last_systick_val = SysTick->VAL;//将上次的计数器的值保存下来以便退出中断后回去时可以从该值继续递减
//		//如果上次记数已经溢出，代表着上次的delay已经记数完成，将该次溢出事件记录下来，以便出了中断回到原delay函数时，可以直接跳出while
//		//delaying_finish是16位的，最多可以记录16次溢出事件，即16层的递归
//		if(SysTick->CTRL & (1 << 16))delaying_finish |= (1 << (delaying_times - 1));
//	}
//	delaying_times ++;
//	SysTick->LOAD = 72 * 1000 * xms;//自动重装载值
//	SysTick->VAL = 0x00;//清除计时器的值
//	SysTick->CTRL |= (1 << 0);//SysTick使能，使能后定时器开始倒数
//	while(!(SysTick->CTRL & (1 << 16)))//判断是否减到0，减到0时CTRL的第16位会置1，读取后会自动置0
//	{
//		//如果在中断中计数器已经溢出，就退出while,并且对应中断位清零
//		if(delaying_finish & (1 << (delaying_times- 1)))
//		{
//			delaying_finish &= ~(1 << (delaying_times- 1));
//			break;
//		}
//	}
//	delaying_times --;
//	if(delaying_times == 0)
//	{
//		SysTick->CTRL &= ~(1 << 0);//关闭SysTick，关闭后记数器将不再倒数
//		SysTick->VAL = 0x00;//清除计时器的值（执行关闭SysTick程序时，记数器又开始了新一轮的倒数，所以关闭后记数器的值不为0）
//	}
//	else
//	{
//		/* 读取CTRL寄存器的同时，CTRL的第16位会变为0，关闭SysTick后给VAL寄存器赋值再使能的原因
//		 * 1.若未关闭SysTick，且先将CTRL的第16位清零后再给VAL寄存器赋值，则在赋值的过程中计数器可能会记数到0，从而导致CTRL的第16位又被置1
//		 * 2.若未关闭SysTick，且先给VAL寄存器赋值后再将CTRL的第16位清零，则在清零的过程中计数器会继续递减并且可能在CTRL的第16位完成清零前就溢出
//		 * 所以必须关闭SysTick，且赋值完需要再使能使得递归回原函数的while中计数器会继续递减
//		 */
//		SysTick->CTRL &= ~(1 << 0);//关闭SysTick，关闭后记数器将不再倒数
//		SysTick->LOAD = last_systick_val;
//		SysTick->VAL = 0x00;//清除计时器的值
//		SysTick->CTRL |= (1 << 0);//SysTick使能，使能后定时器开始倒数
//	}
//}
// 
///**
//  * @brief  秒级延时
//  * @param  xs 延时时长，范围：0~4294967295
//  * @retval 无
//  */
//void Delay_s(uint32_t xs)
//{
//	while(xs--)
//	{
//		Delay_ms(1000);
//	}
//} 

