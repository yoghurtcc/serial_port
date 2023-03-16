// answer.cpp
//this source used for talking
//just a example 
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/MultiArrayDimension.h"
#include <sstream>
#include "serialpost.hpp"

int ros_post_pc(const uint8_t  buffer,ros::Publisher chatter_pub){
        std_msgs::UInt8MultiArray  msg;
        msg.data.resize(64);
        msg.data[0]=0xac;
        msg.data[1]=0xbb;
        msg.data[2]=buffer;
        msg.data[3]=0xff;
        chatter_pub.publish(msg);   
        ros::spinOnce();   
}

//use this fuction 
void chatterMPUCallback(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{
 // ROS_INFO("I heard: [%x]", msg->data[0]);//
}

int main(int argc, char **argv)
{
    //init  ros
    ros::init(argc, argv, "talker");
    //init nodehandler
    ros::NodeHandle n;   
    //pulish chatter
    ros::Publisher chatter_pub = n.advertise<std_msgs::UInt8MultiArray>("chatter_pc", 1000);
    ros::Subscriber sub = n.subscribe("chatter_mpu", 1000, chatterMPUCallback);
    //loop rate
    ros::Rate loop_rate(10); 
    //counting for chatting
    int count = 0;

  while (ros::ok())
  {
  ros_post_pc (30,chatter_pub);
    //sleep for a while
    loop_rate.sleep();
    ++count;
  }

  return 0;
}
