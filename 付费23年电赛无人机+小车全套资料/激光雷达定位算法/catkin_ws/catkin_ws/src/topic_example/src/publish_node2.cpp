
#include "ros/ros.h"
#include "std_msgs/String.h" //use data struct of std_msgs/String  
#include "mbot_linux_serial.h"


//test receive value
double testRece1=0.0;
double testRece2=0.0;
double testRece3=0.0;

int flag = 0;
unsigned char testRece4=0x00;

int main(int agrc,char **argv)
{
    ros::init(agrc,argv,"publish_node2");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("syscommand",10);

    ros::Rate loop_rate(10);
    
    //串口初始�?    
    serialInit();

    while(ros::ok())
    {
         ros::Time now=ros::Time::now();
        ros::spinOnce();
        //从STM32接收数据，输入参数依次转化为小车的线速度、角速度、航向角（角度）、预留控制位
	    readSpeed(testRece1,testRece2,testRece3,testRece4);
        //打印数据
        if(testRece1==0)
        {
            flag = 1;
        }
        if(testRece1==5000&&flag == 1)
        {
            std_msgs::String msg;
            msg.data = "reset";
            pub.publish(msg);
            flag = 0;
        }
	    ROS_INFO("%f,%f,%f,%d\n",testRece1,testRece2,testRece3,testRece4);
        loop_rate.sleep();
    }
    return 0;
}
 



