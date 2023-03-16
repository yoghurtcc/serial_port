 #include "serialport.hpp"

uint8_t send_buffer [64];

//the callback of node
void chatterCallback(const std_msgs::UInt8MultiArray::ConstPtr& msg)
{
   for (size_t i = 0; i < 64; i++)
        {
            send_buffer[i]=msg->data[i];
        }
}

//main body
int main(int argc, char** argv)
{
    ros::init(argc, argv, "serial_port_basic");
    //create a nodehandle
    ros::NodeHandle n;    
    //create a serial class
    serial::Serial sp;
    //chatter fuction
    ros::Publisher chatter_pub = n.advertise<std_msgs::UInt8MultiArray>("chatter_mpu", 1000);
    ros::Subscriber sub = n.subscribe("chatter_pc", 1000, chatterCallback);
    //create the timeout warning
    serial::Timeout to = serial::Timeout::simpleTimeout(10);
    //edit the port (for the first serial port the ch340 connected is ttyUSB0)
    sp.setPort("/dev/ttyUSB0");
    //set baudrate
    sp.setBaudrate(115200);
    //set seial timeout
    sp.setTimeout(to); 

    try{
        //open port
        sp.open();
    }
    catch(serial::IOException& e){
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }

    if(sp.isOpen()){
        ROS_INFO_STREAM("serial is opened.");
    }else{
        return -1;
    }

    //control the rate of loop
    ros::Rate loop_rate(100);

    while(ros::ok())
    {   //open the subscriber for once 
        ros::spinOnce();
        //read from linux buffer
        size_t n = sp.available();
        if(n!=0)
        {
            //the lagest buffer place is 64 x hex 
            uint8_t buffer[64];
            //put the data into buffer
            n = sp.read(buffer, n);
           int err =  buffer_read(buffer);
            ros_post_mpu(buffer,chatter_pub );
        }
        sp.write(send_buffer, n);
        //wait for the next turn
        loop_rate.sleep();
    }
    //close the port
    sp.close();
    return 0;
}

