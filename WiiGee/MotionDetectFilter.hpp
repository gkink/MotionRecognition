//
//  MotionDetectFilter.hpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef MotionDetectFilter_hpp
#define MotionDetectFilter_hpp

class Device;

#include <stdio.h>
#include "Filter.hpp"

class MotionDetectFilter: public Filter{
    
public:
    MotionDetectFilter(Device *dev):Filter(), device{dev} {
        this->reset();
    }
    void reset();
    vector<double>& filterAlgorithm(vector<double>& vec);
    void setSensivity(double sensivity);
    double getSensivity();
    vector<double>& filter(vector<double>& vec);
    void setMotionChangeTime(int time);
    int getMotionChangeTime();
    
private:
    int motionchangetime;
    bool nowinmotion;
    long long motionstartstamp;
    Device *device;
    long long getCurrentTime();
    
};

#endif /* MotionDetectFilter_hpp */
