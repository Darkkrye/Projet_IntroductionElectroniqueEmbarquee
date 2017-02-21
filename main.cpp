#include "mbed.h"
#include "wheel.h"
#include "vehicle.h"

#define null                    0

#define LEFT_WHEEL              0
#define RIGHT_WHEEL             1

#define LEFT_WHEEL_POWER        D3
#define LEFT_WHEEL_ORIENTATION  D2

#define RIGHT_WHEEL_POWER       D11
#define RIGHT_WHEEL_ORIENTATION D10

#define CAPTOR_LEFT             D6
#define CAPTOR_FRONT            D5
#define CAPTOR_RIGHT            D7

#define callWait(a,b)           a;wait(b);


#define SPEED_NORMAL            0.3f, 0.3f
//#define SPEED_NORMAL            0.8f, 0.8f
#define SPEED_SEARCH            0.2f, 0.2f


#define SPEED_EXTREME_LEFT      0.0f, 1.0f
#define SPEED_LEFT              0.3f, 0.6f

#define SPEED_EXTREME_RIGHT     1.0f, 0.0f
#define SPEED_RIGHT             0.6f, 0.3f

#define S_EXTREME_RIGHT         0
#define S_RIGHT                 1
#define S_MIDDLE                2
#define S_LEFT                  3
#define S_EXTREME_LEFT          4

#define C_FORWARD               0
#define C_DETERMINATE           1
#define C_SEARCH                2

DigitalOut leds[ 4 ] = {
    DigitalOut( D15 ), DigitalOut( D14 ), DigitalOut( D13 ), DigitalOut( D12 )
};

AnalogIn sensors[ 5 ] = {
    AnalogIn( A0 ), AnalogIn( A1 ), AnalogIn( A2 ), AnalogIn( A3 ), AnalogIn( A4 )
};

float flAverage[ 5 ], flCritical[ 5 ];

Serial pc(SERIAL_TX, SERIAL_RX);
bool isOnBlack( int iSensor );

int iMillis;
bool bRightPriorityDetected = false;
bool bAbleToMove = true;

int main( ) {
    Vehicle vehicle; 
    vehicle.setLeftWheel( LEFT_WHEEL_POWER, LEFT_WHEEL_ORIENTATION );
    vehicle.setRightWheel( RIGHT_WHEEL_POWER, RIGHT_WHEEL_ORIENTATION );
    
    for( int i = 0; i < 4; i ++ ) {
        leds[ i ].write( 1 );
    }
    
    wait( 0.5 );
    
    int i = 0;
    int iCase = C_FORWARD;
    bAbleToMove = true;
    bRightPriorityDetected = false;
    
    for( i = 0; i < 5; i ++ ) {
        flAverage[ i ] = sensors[ i ].read( );
        
        if( i == 2 ) {
            flCritical[ i ] = flAverage[ i ] * 0.85f;
            //flCritical[ i ] = flAverage[ i ] * 0.65f;
        } else {
            flCritical[ i ] = flAverage[ i ] * 1.1f;
            //flCritical[ i ] = flAverage[ i ] * 1.2f;
        }
    }
    
    DigitalIn CaptorLeft( CAPTOR_LEFT ), CaptorFront( CAPTOR_FRONT ), CaptorRight( CAPTOR_RIGHT );
    
    bool bTurnExtremeLeft = false, bTurnExtremeRight = false;
    
    while( 1 ) {
        
        if( bRightPriorityDetected == true ) {
            if( CaptorRight.read( ) == 0 || CaptorFront.read( ) == 0 ) {
                vehicle.stop( );
                bAbleToMove = false;
            } else {
                if( CaptorLeft.read( ) == 0 ) {
                    bRightPriorityDetected = false;
                }
                    
                 bAbleToMove = true;
            }
        }
        
        if( bAbleToMove == true ) {
            if( isOnBlack( S_MIDDLE ) && isOnBlack( S_RIGHT ) && isOnBlack( S_EXTREME_RIGHT ) ) {
                bRightPriorityDetected = true;
                iMillis = 0;
            }
            
            switch( iCase ) {
                case C_FORWARD: {
                    if( isOnBlack( S_MIDDLE ) ) {
                        vehicle.move(O_FORWARD, SPEED_NORMAL );
                    } else {
                        vehicle.stop( );
                        iCase = C_DETERMINATE;
                    }
                    
                    break;
                }
                case C_DETERMINATE: {
                    while( isOnBlack( S_MIDDLE ) == false ) {
                        if( isOnBlack( S_RIGHT ) ) {
                            if( isOnBlack( S_EXTREME_RIGHT ) ) {
                                vehicle.move(O_FORWARD, SPEED_EXTREME_RIGHT);
                                bTurnExtremeRight = true;
                            } else {
                                vehicle.move(O_FORWARD, SPEED_RIGHT);
                                bTurnExtremeRight = false;
                            }
                            
                            bTurnExtremeLeft = false;
                        } else if( isOnBlack( S_LEFT ) ) {
                            if( isOnBlack( S_EXTREME_LEFT ) ) {
                                bTurnExtremeLeft = true;
                                vehicle.move(O_FORWARD, SPEED_EXTREME_LEFT);
                            } else {
                                vehicle.move(O_FORWARD, SPEED_LEFT);
                                bTurnExtremeLeft = false;
                            }
                            bTurnExtremeRight = false;
                            
                        } else if( isOnBlack( S_EXTREME_RIGHT ) ) {
                            bTurnExtremeLeft = true;
                            vehicle.move(O_FORWARD, SPEED_EXTREME_RIGHT);
                        } else if( isOnBlack( S_EXTREME_LEFT ) ) {
                            bTurnExtremeRight = true;
                            vehicle.move(O_FORWARD, SPEED_EXTREME_LEFT);
                        }
                        else {
                            if( bTurnExtremeLeft == true ) {
                                vehicle.move(O_FORWARD, SPEED_EXTREME_LEFT);
                            } else if( bTurnExtremeRight == true ) {
                                vehicle.move(O_FORWARD, SPEED_EXTREME_RIGHT);
                            } else {
                                vehicle.move( O_FORWARD, SPEED_SEARCH ); 
                            }
                        }
                    }
                    
                    iCase = C_FORWARD;
                    
                    break;
                }
            }
        }
    }
}

bool isOnBlack( int iSensor ) {
    return sensors[ iSensor ].read( ) > flCritical[ iSensor ];
}