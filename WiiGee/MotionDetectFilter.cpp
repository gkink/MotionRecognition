//
//  MotionDetectFilter.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "MotionDetectFilter.hpp"
#include <chrono>

void MotionDetectFilter::reset() {
    this->motionstartstamp = getCurrentTime();
    this->nowinmotion = false;
    this->motionchangetime = 190;
}

long long MotionDetectFilter::getCurrentTime(){
    auto timePoint = std::chrono::system_clock::now().time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint).count();
    return milliseconds;
}


vector<double>& MotionDetectFilter::filter(vector<double>& vec) {
    
    if (this->nowinmotion &&
            (getCurrentTime() - this->motionstartstamp) >=
            this->motionchangetime) {
        this->nowinmotion = false;
        this->device->fireMotionStopEvent();
    }
    
    return filterAlgorithm(vec);
}

vector<double>& MotionDetectFilter::filterAlgorithm(vector<double>& vec) {
    if(!vec.empty()) {
        this->motionstartstamp = getCurrentTime();
        if(!this->nowinmotion) {
            this->nowinmotion = true;
            this->motionstartstamp = getCurrentTime();
            this->device->fireMotionStartEvent();
        }
    }
    
    return vec;
}


void MotionDetectFilter::setMotionChangeTime(int time) {
    this->motionchangetime = time;
}

int MotionDetectFilter::getMotionChangeTime() {
    return this->motionchangetime;
}
