//
//  Gesture.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef Gesture_hpp
#define Gesture_hpp

#include <vector>
#include "AccelerationEvent.hpp"
#include <memory>

using namespace std;

class Gesture{

public:
    Gesture(){}
    Gesture(shared_ptr<Gesture> original);
    void add(shared_ptr<AccelerationEvent> event);
    shared_ptr<AccelerationEvent> getLastData();
    vector<shared_ptr<AccelerationEvent>> &getData();
    void removeFirstData();
    size_t getCountOfData();
    void setMaxAndMinAcceleration(double max, double min);
    double getMaxAcceleration();
    double getMinAcceleration();
    
private:
    bool minmaxmanual;
    double minacc;
    double maxacc;
    vector<shared_ptr<AccelerationEvent>> data;
};

#endif /* Gesture_hpp */
