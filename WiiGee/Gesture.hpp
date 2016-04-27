//
//  Gesture.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef Gesture_hpp
#define Gesture_hpp

#include <stdio.h>
#include <vector>
#include "AccelerationEvent.hpp"

using namespace std;

class Gesture{

public:
    Gesture(){}
    Gesture(Gesture &original);
    void add(AccelerationEvent event);
    AccelerationEvent getLastData();
    vector<AccelerationEvent> &getData();
    void removeFirstData();
    size_t getCountData();
    void setMaxAndMinAcceleration(double max, double min);
    double getMaxAcceleration();
    double getMinAcceleration();
    
private:
    bool minmaxmanual;
    double minacc;
    double maxacc;
    vector<AccelerationEvent> data;
};

#endif /* Gesture_hpp */
