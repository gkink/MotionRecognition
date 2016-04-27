//
//  AccelerationEvent.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "AccelerationEvent.hpp"

AccelerationEvent::AccelerationEvent(double X, double Y, double Z, double absvalue) {
    this->X=X;
    this->Y=Y;
    this->Z=Z;
    this->absvalue=absvalue;
}

double AccelerationEvent::getX() {
    return X;
}

double AccelerationEvent::getY() {
    return Y;
}

double AccelerationEvent::getZ() {
    return Z;
}

double AccelerationEvent::getAbsValue() {
    return absvalue;
}