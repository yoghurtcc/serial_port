#ifndef  __READ_H__
#define __READ_H__

#include <ros/ros.h>
#include <serial/serial.h>
#include <iostream>
#include<stdio.h>
#include "serialread.hpp"
#include "serialpost.hpp"

 //the example write to analyse the hex code
int buffer_read(uint8_t *buffer);

//gy25_data
class raw_data
{
    public :
    int16_t ACC_X;
    int16_t ACC_Y;
    int16_t ACC_Z;

    int16_t GYRO_X;
    int16_t GYRO_Y;
    int16_t GYRO_Z;

    int16_t YAW;
    int16_t PITCH;
    int16_t ROLL;    
};

class unit_data
{
    public :
    float ACC_X;            //m/s^2
    float ACC_Y;
    float ACC_Z;

    float GYRO_X;           //rads/s
    float GYRO_Y;
    float GYRO_Z;

    float YAW;              //degree
    float PITCH;
    float ROLL;
};

class gy25_data
{
    public :
    raw_data gy25_raw_data;
    unit_data gy25_unit_data;
};
//crc
//


#endif
