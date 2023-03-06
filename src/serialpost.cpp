#include "serialpost.hpp"

int ros_post_mpu(const uint8_t *buffer,ros::Publisher chatter_pub){
        std_msgs::UInt8MultiArray  msg;
        msg.data.resize(64);
        for (size_t i = 0; i < 64; i++)
        {
            msg.data[i]=buffer[i];
        }
        chatter_pub.publish(msg);   
        ros::spinOnce();   
}
