#include "timer.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"	
//TIMER3���жϷ������
//void TIM3_IRQHandler(void)
//{
//	if(TIM3->SR&0x0001) LED1 = !LED1;		//���
//	TIM3->SR&=~(1<<0);
//}

void TIM2_3_PWM_Init(u16 arr, u16 psc)
{
	RCC->APB1ENR |= ((1<<0)+(1<<1));		//TIM2 3ʱ��ʹ��
	GPIOA->CRL&=0x00FF0000;
	GPIOA->CRL|=0xbb00bbbb;

	TIM2->ARR = arr;TIM3->ARR = arr;			//Ԥ����װֵ
	TIM2->PSC = psc;TIM3->PSC = psc;			//Ԥ��Ƶ��720 ���100khz�ļ���ʱ��

	TIM2->CR1=0x0080;TIM3->CR1=0x0080;			   	//ARPEʹ��
	TIM2->CR1 |= 0X01;TIM3->CR1 |= 0X01;			//ʹ�ܶ�ʱ��
	
	TIM2->CCMR1|=7<<4;				//PWM2ģʽ����
	TIM2->CCMR1|=7<<12;  	
	TIM2->CCMR2|=7<<4;
	TIM2->CCMR2|=7<<12;
	TIM3->CCMR1|=7<<4;
	TIM3->CCMR1|=7<<12;
	
	TIM2->CCMR1|=1<<3;				//Ԥװ��ʹ��	
	TIM2->CCMR1|=1<<11; 
	TIM2->CCMR2|=1<<3;
	TIM2->CCMR2|=1<<11;
	TIM3->CCMR1|=1<<3;
	TIM3->CCMR1|=1<<11;
	
 	TIM2->CCER|=((1<<0) + (1<<4) + (1<<8) + (1<<12));   	//OC���ʹ��	   
	TIM3->CCER|=((1<<0) + (1<<4));
 
	
	CH1_PWM_VAL = 250;
	CH2_PWM_VAL = 250;
	CH3_PWM_VAL = 250;
	CH4_PWM_VAL = 250;
	CH5_PWM_VAL = 250;
	CH6_PWM_VAL = 250;
	
//	TIM3->DIER |= 1<<0;			//��������ж�
//	MY_NVIC_Init(1,3,TIM3_IRQn,2);	//��ռ1 ��Ӧ2 ��2
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
