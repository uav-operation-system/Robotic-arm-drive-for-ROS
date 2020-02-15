#include "timer.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	
//TIMER3的中断服务程序
//void TIM3_IRQHandler(void)
//{
//	if(TIM3->SR&0x0001) LED1 = !LED1;		//溢出
//	TIM3->SR&=~(1<<0);
//}

void TIM2_3_PWM_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR |= ((1<<0)+(1<<1));		//TIM2 3时钟使能
	GPIOA->CRL&=0x00FF0000;
	GPIOA->CRL|=0xbb00bbbb;

	TIM2->ARR = arr;TIM3->ARR = arr;			//预载重装值
	TIM2->PSC = psc;TIM3->PSC = psc;			//预分频器720 获得100khz的计数时钟

	TIM2->CR1=0x0080;TIM3->CR1=0x0080;			   	//ARPE使能
	TIM2->CR1 |= 0X01;TIM3->CR1 |= 0X01;			//使能定时器
	
	TIM2->CCMR1|=7<<4;				//PWM2模式设置
	TIM2->CCMR1|=7<<12;  	
	TIM2->CCMR2|=7<<4;
	TIM2->CCMR2|=7<<12;
	TIM3->CCMR1|=7<<4;
	TIM3->CCMR1|=7<<12;
	
	TIM2->CCMR1|=1<<3;				//预装载使能	
	TIM2->CCMR1|=1<<11; 
	TIM2->CCMR2|=1<<3;
	TIM2->CCMR2|=1<<11;
	TIM3->CCMR1|=1<<3;
	TIM3->CCMR1|=1<<11;
	
 	TIM2->CCER|=((1<<0) + (1<<4) + (1<<8) + (1<<12));   	//OC输出使能	   
	TIM3->CCER|=((1<<0) + (1<<4));
 
	
	CH1_PWM_VAL = 250;
	CH2_PWM_VAL = 250;
	CH3_PWM_VAL = 250;
	CH4_PWM_VAL = 250;
	CH5_PWM_VAL = 250;
	CH6_PWM_VAL = 250;
	
//	TIM3->DIER |= 1<<0;			//允许更新中断
//	MY_NVIC_Init(1,3,TIM3_IRQn,2);	//抢占1 响应2 组2
}


void Rds_Control(int ang,int serial_num)
{
	switch(serial_num)
	{
		case 1:	CH1_PWM_VAL = (150 + 200*ang/270);break;
		case 2:	CH2_PWM_VAL = (150 + 200*ang/270);break;
		case 3:	CH3_PWM_VAL = (150 + 200*ang/270);break;
		case 4:	CH4_PWM_VAL = (150 + 200*ang/270);break;
		case 5:	CH5_PWM_VAL = (150 + 200*ang/270);break;
		case 6:	CH6_PWM_VAL = (150 + 200*ang/270);break;
		default:printf("wrong steering number");
	}
}
