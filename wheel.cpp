#include "wheel.h"

Wheel::Wheel( PwmOut * speed, DigitalOut * orientation ) {
    this->speed = speed;
    this->orientation = orientation;
}

Wheel::~Wheel( ) {
    delete this->speed;
    delete this->orientation;
}

void Wheel::setPower( float flSpeed ) {
    this->speed->write( flSpeed );
}

float Wheel::getPower( ) {
    return this->speed->read( ); 
}
        
void Wheel::setOrientation( int iOrientation ) {
    this->orientation->write(iOrientation);
}

int Wheel::getOrientation( ) {
    return this->orientation->read();
}
        
void Wheel::setState( float flSpeed, int iOrientation ) {
    this->setPower( flSpeed );
    this->setOrientation( iOrientation );
}