TIM2 3

舵机号-通道-引脚

1 tim2-ch1 pa0

2 tim2-ch2 pa1

3 tim2-ch3 pa2

4 tim2-ch4 pa3

5 tim3-ch1 pa6

6 tim3-ch2 pa7

串口通信配置函数里面默认最后两位应该是0x0d作为校验(不包括在打印的数据长度中),如果ros跟32通信要校验码之类的可以保留着,如果单纯只是一组一组地发送六路舵机的转动角度,我可以把那个校验给删掉

现在ros给32发送数据的格式是xx xx xx xx xx xx 0d,16进制发送,前面6对16进制数是1-6号舵机的角度(高位 * 16+低位,因为只要0-180度控制所以两位就够),后面的是校验码0d0a
