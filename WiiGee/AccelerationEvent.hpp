//
//  AccelerationEvent.hpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef AccelerationEvent_hpp
#define AccelerationEvent_hpp

#include <stdio.h>
#include "Device.hpp"

class AccelerationEvent {
    /**
     * Create an AccelerationEvent with a specific source,
     * all the three acceleration values and the calculated absolute
     * value.
     *
     * @param source The source which has been accelerated (Wiimote).
     * @param X The value of acceleration in the x direction.
     * @param Y The value of acceleration in the y direction.
     * @param Z The value of acceleration in the z direction.
     * @param absvalue The absolute value of this acceleration vector.
     */
public:
    
    AccelerationEvent(double X, double Y, double Z, double absvalue);
    double getX();
    double getY();
    double getZ();
    double getAbsValue();
        
private:
    double X, Y, Z;
    double absvalue;
};

#endif /* AccelerationEvent_hpp */
