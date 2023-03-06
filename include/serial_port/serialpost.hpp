#ifndef __POST_H__
#define __POST_H__

#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/MultiArrayDimension.h"

int ros_post_mpu(const uint8_t *buffer,ros::Publisher chatter_pub);

#endif