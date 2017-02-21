#ifndef WHEEL_HEADER___
#define WHEEL_HEADER___

#include "mbed.h"

#define ORIENTATION_FORWARD 1
#define ORIENTATION_BACKWARD 0

class Wheel {
    private: 
        PwmOut * speed;
        DigitalOut * orientation;
        
    public: 
        Wheel( PwmOut * speed, DigitalOut * orientation );
        ~ Wheel( );
        
        void setPower( float flSpeed );
        float getPower( );
        
        void setOrientation( int iOrientation );
        int getOrientation( );
        
        void setState( float flSpeed, int iOrientation );
};
#endif