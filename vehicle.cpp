#include "vehicle.h"

Vehicle::Vehicle( ) {
    mLeftWheel = 0;
    mRightWheel = 0;
}

Vehicle::~ Vehicle( ) {
    if( mRightWheel != 0 ) 
        delete mRightWheel;
    if( mLeftWheel != 0 )
        delete mLeftWheel;
}

/*void Vehicle::avancer( ) {
    mLeftWheel->setState(1.0,1);
    mRightWheel->setState(0.5,1);
}
*/


/*void Vehicle::reculer( ) {
    mLeftWheel->setState(1,0);
    mRightWheel->setState(1,0);
}



void Vehicle::droite( ) {
    mLeftWheel->setState(1,1);
    mRightWheel->setState(0,0);
}

void Vehicle::gauche( ) {
    mLeftWheel->setState(0,0);
    mRightWheel->setState(1,1);
}
*/
void Vehicle::move( int iOrientation, float flLeftSpeed, float flRightSpeed ) {
    mLeftWheel->setState(flLeftSpeed, iOrientation);
    mRightWheel->setState(flRightSpeed, iOrientation);
}

void Vehicle::stop( ) {
    this->move( 0, 0.0f );
}

void Vehicle::move( int iOrientation, float flSpeed ) {
    move( iOrientation, flSpeed, flSpeed );
}

void Vehicle::setRightWheel( Wheel * wheel ) {
    this->mRightWheel = wheel;
}

void Vehicle::setLeftWheel( Wheel * wheel ) {
    this->mLeftWheel = wheel;
}

void Vehicle::setRightWheel( PinName power, PinName orientation ) {
    this->mRightWheel = new Wheel( new PwmOut( power ), new DigitalOut( orientation ) );
}

void Vehicle::setLeftWheel( PinName power, PinName orientation ) {
    this->mLeftWheel = new Wheel( new PwmOut( power ), new DigitalOut( orientation ) );
}