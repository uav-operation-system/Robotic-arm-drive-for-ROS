#include <ros/ros.h>
#include <serial/serial.h>
#include <iostream>
#include <sensor_msgs/JointState.h>

serial::Serial sp;//串口对象

void jointstatesCallback(const sensor_msgs::JointStateConstPtr& msg)
{
    float_t pos[6];
    pos[0]=msg->position[0];
    pos[1]=msg->position[1];
    pos[2]=msg->position[2];
    pos[3]=msg->position[3];
    pos[4]=msg->position[4];
    pos[5]=msg->position[5];
    ROS_INFO("pos[0]:[%f] pos[1]:[%f] pos[2]:[%f] pos[3]:[%f] pos[4]:[%f] pos[5]:[%f]",pos[0],pos[1],pos[2],pos[3],pos[4],pos[5]);
    sp.write((uint8_t*)pos,6*4);
}

int main(int argc, char** argv)
{
 ros::init(argc, argv, "serial_port");  //定义节点
 /*串口*/
 ros::Time::init();
 serial::Timeout to = serial::Timeout::simpleTimeout(100);//serial_timeout
 sp.setPort("/dev/ttyUSB0"); 
 sp.setBaudrate(38400);  //波特率
 sp.setTimeout(to);     //串口设置timeout
 try
    {  
        sp.open();  //打开串口
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    if(sp.isOpen())//判断串口是否打开成功
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
sp.write("Hello");//写串口
ros::Rate loop_rate(10);  //休眠10hz  

 /*回调函数*/
ros::NodeHandle n;
 ros::Subscriber sub = n.subscribe("joint_states", 1000, &jointstatesCallback);  //回调函数
ros::spin();
}

/*
//回调函数
void jointstatesCallback(const sensor_msgs::JointStateConstPtr& msg)
{
    std::cout<<"called_back"<<std::endl;
    //uint8_t buffer[1024];
    //int i;
    size_t pos[6]; // pos=msg.position;  
    pos[0]=msg->position[0];
    pos[1]=msg->position[1];
    pos[2]=msg->position[2];
    pos[3]=msg->position[3];
    pos[4]=msg->position[4];
    pos[5]=msg->position[5];
    ROS_INFO("pos[0]:[%f] pos[1]:[%f] pos[2]:[%f]",pos[0],pos[0],pos[0]);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "serial_port");               //serial_port节点
    //创建句柄（虽然后面没用到这个句柄，但如果不创建，运行时进程会出错）
    ros::NodeHandle n;
    //创建一个订阅话题   
    ros::Subscriber sub = n.subscribe("joint_states",1,jointstatesCallback);   
    serial::Serial sp; //创建一个serial对象
    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyUSB0");
    //设置串口通信的波特率
    sp.setBaudrate(115200);
    //串口设置timeout
    sp.setTimeout(to);
 
    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
    
    ros::Rate loop_rate(10);  //origin=500   
    while(ros::ok()) 
    {
//	    ros::Subscriber sub = n.subscribe("joint_states",1,jointstatesCallback);
        //获取缓冲区内的字节数
        size_t n = sp.available();
        if(n!=0)
        {
            uint8_t buffer[1024];
            //读出数据
            n = sp.read(buffer, n);
            
            for(int i=0; i<n; i++)
            {
                //16进制的方式打印到屏幕
                std::cout << std::hex << (buffer[i] & 0xff) << " ";
            }
            std::cout << std::endl;
            //把数据发送回去
            sp.write(buffer, n);
        }  
	    
        loop_rate.sleep();
    }
    
    //关闭串口
    sp.close();
 
    return 0;
}
*/
