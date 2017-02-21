#ifndef VEHICLE_HEADER___
#define VEHICLE_HEADER___

#include "wheel.h"
#include "mbed.h"

#define O_FORWARD   1
#define O_BACKWARD  0

#define SPEED_MAX   1.0f
#define SPEED_SLOW  0.1f
#define SPEED_STOP  0.0f

class Vehicle {
    private: 
        Wheel * mLeftWheel;
        Wheel * mRightWheel;
    public:
        
        Vehicle( );
        ~ Vehicle( );
        
        void stop( );
        void setRightWheel( Wheel * wheel );
        void setLeftWheel( Wheel * wheel );
        void move( int iOrientation, float flSpeed );
        void move( int iOrientation, float flLeftSpeed, float flRightSpeed );
        void setRightWheel( PinName power, PinName orientation );
        void setLeftWheel( PinName power, PinName orientation );
};
#endif