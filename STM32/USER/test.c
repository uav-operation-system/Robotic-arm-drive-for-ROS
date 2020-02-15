#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "timer.h" 
//ALIENTEK Mini STM32开发板范例代码8
//PWM输出实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{			   
	int ang[6]={0}; u8 len,t;
	
	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	TIM2_3_PWM_Init(2000-1,720-1);//PWM频率100k 周期20ms 初始化舵角归零
	delay_ms(1000);
	
	//串口获取6路舵角,控制舵机并打印对应的舵角和接收的数据长度(字节)
	while(1)
	{
		if(USART_RX_STA&0X8000)
		{	
			len = USART_RX_STA&0X3FFF;			//得到此次接收数据的长度
			for(t=0;t<len;t++)
			{
				printf(" %d ",USART_RX_BUF[t]);
				ang[t] = USART_RX_BUF[t];
				Rds_Control(ang[t],t+1);
			}
			printf("len %d",len);
			printf("\r\n\r\n");						//插入换行
			USART_RX_STA = 0;
		}
		else delay_ms(10);
	}

}



