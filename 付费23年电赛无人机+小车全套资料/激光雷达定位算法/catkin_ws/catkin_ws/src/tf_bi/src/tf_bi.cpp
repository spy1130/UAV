#include <ros/ros.h>
#include <tf/transform_listener.h>
int main(int argc, char** argv){
    ros::init(argc, argv, "demo_tf_listener");  //初始化一个监听器
 
    ros::NodeHandle n; //创建一个句柄
 
    tf::TransformListener listener; //声明一个监听器 
 
    float saved_rx = 0.0;
    float saved_ry = 0.0;
    float saved_rz = 0.0;
 
    ros::Rate rate(10.0);
    while (ros::ok()){
        tf::StampedTransform transform;
 
        try{
            ros::Time now=ros::Time::now();
            //订阅的是以robot作为父坐标系，world为子坐标系
            listener.waitForTransform("map","odom_combined",now,ros::Duration(1.0));
            listener.lookupTransform("/map", "/odom_combined",now, transform);
            saved_rx = transform.getOrigin().x();
            saved_ry = transform.getOrigin().y();
            saved_rz = transform.getOrigin().z();
            ROS_INFO("Transform rotation(RPY) received is %f %f %f",saved_rx,saved_ry,saved_rz);
 
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        ROS_INFO("Saved transform is %f %f %f",saved_rx,saved_ry,saved_rz);
        rate.sleep();
    }
  return 0;
}
