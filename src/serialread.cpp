#include "serialread.hpp"

gy25_data gy25;
uint16_t row_raw,yaw_raw,pitch_raw=0;
float row,yaw,pitch=0;
float accx,accy,accz=0;

int buffer_read(uint8_t *buffer){
    int max_size=64;
    int status=0;
    //the head of the serial port is 0xAE
    if(buffer[0]==0xAE){
        status=1;
    }else {
        return 0;
    }
   //choose the mod of the receiving data
   switch(buffer[1]){
        case 0xAA:
            status=2;
            break;
        default:
            return 0;
            break;
   }
   //the fuction that write for an example
    if(status==2)
    {
        if(buffer[20]==0xFF)
        {
            gy25.gy25_raw_data.ROLL=(int16_t)((buffer[15] | ((int16_t)buffer[14] << 8)));
            gy25.gy25_raw_data.PITCH=(int16_t)((buffer[17] | ((int16_t)buffer[16] << 8)));
            gy25.gy25_raw_data.YAW=(int16_t)((buffer[19] | ((int16_t)buffer[18] << 8)));
            gy25.gy25_unit_data.ROLL= gy25.gy25_raw_data.ROLL/100;
            gy25.gy25_unit_data.PITCH=gy25.gy25_raw_data.PITCH/100;
            gy25.gy25_unit_data.YAW = gy25.gy25_raw_data.YAW/100;
            printf("roll=%f , pitch=%f , yaw=%f\n",gy25.gy25_unit_data.ROLL,gy25.gy25_unit_data.PITCH,gy25.gy25_unit_data.YAW);
        }else{
            return 0;
        }
    }else{
        return 0;
    }
    //report error
    return status;

}
