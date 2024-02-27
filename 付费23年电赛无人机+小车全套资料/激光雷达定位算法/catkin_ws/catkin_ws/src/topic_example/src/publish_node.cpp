
#include "ros/ros.h"
#include "std_msgs/String.h" //use data struct of std_msgs/String  
#include "mbot_linux_serial.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
//test send value
float testSend1=0.0;
float testSend2=0.0;
unsigned char testSend3=42;
int testSend1s=0.0;
int testSend2s=0.0;

void bi_callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{       
         ROS_INFO("the position(x,y,z) is %f , %f, %f", msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
        testSend1 = msg->pose.pose.position.x;
        testSend2 = msg->pose.pose.position.y;
        testSend1s =(double) testSend1*1000;
        testSend2s =(double)testSend2*1000;
        writeSpeed(testSend1s,testSend2s,testSend3);
}

int main(int agrc,char **argv)
{
    ros::init(agrc,argv,"publish_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("poseupdate",1,bi_callback);
  // ros::Rate rate(10);
    
    serialInit();

    while(ros::ok())
    {
        
        ros::spinOnce();
      //  rate.sleep();
    }
    return 0;
}

