// answer.cpp
//this source used for talking
//just a example 
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/MultiArrayDimension.h"
#include <sstream>
#include "serialpost.hpp"

//use this fuction 
void chatterMPUCallback(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{
  ROS_INFO("I heard: [%x]", msg->data[0]);
}

int main(int argc, char **argv)
{
    //init  ros
    ros::init(argc, argv, "talker");
    //init nodehandler
    ros::NodeHandle n;   
    //pulish chatter
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter_pc", 1000);
    ros::Subscriber sub = n.subscribe("chatter_mpu", 1000, chatterMPUCallback);
    //loop rate
    ros::Rate loop_rate(10); 
    //counting for chatting
    int count = 0;

  while (ros::ok())
  {
    //use for message transporting
    std_msgs::String msg;  
    std::stringstream ss;
    //report
    ss << "hello world " << count;
    msg.data = ss.str();
    //log
    ROS_INFO("%s", msg.data.c_str());
    //publish core
    chatter_pub.publish(msg); 
    //spin for once
    ros::spinOnce();  
    //sleep for a while
    loop_rate.sleep();
    ++count;
  }

  return 0;
}
