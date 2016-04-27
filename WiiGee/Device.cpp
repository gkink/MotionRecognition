//
//  Device.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "Device.hpp"
#include "Filter.hpp"
#include "IdleStateFilter.hpp"
#include "MotionDetectFilter.hpp"
#include "DirectionalEquivalenceFilter.hpp"
#include <memory>
#include <vector>
#include <math.h>
#include "Quantizer.hpp"

Device::Device(bool autofiltering){
    if (autofiltering) {
        this->addAccelerationFilter(unique_ptr<IdleStateFilter>( new IdleStateFilter()));
        this->addAccelerationFilter(unique_ptr<MotionDetectFilter>(new MotionDetectFilter(this)));
        this->addAccelerationFilter(unique_ptr<DirectionalEquivalenceFilter>(new DirectionalEquivalenceFilter()));
    }
    this->addAccelerationListener(this->processingunit);
    this->addButtonListener(this->processingunit);
}

void Device::addAccelerationFilter(unique_ptr<Filter> filter){
    this->accFilters.push_back(filter);
}

void Device::addAccelerationListener(unique_ptr<AccelerationListener> listener){
    this->accelerationlistener.push_back(listener);
}

void Device::resetAccelerationFilters(){
    for (int i = 0; i < this->accfilters.size(); i++) {
        this->accfilters.at(i).reset();
    }
}

void Device::addGestureListener(unique_ptr<GestureListener> listener){
    this->processingunit->addGestureListener(listener);
}

void Device::addButtonListener(unique_ptr<ButtonListener> listener){
    this->buttonlistener.push_back(listener);
}

void Device::fireAccelerationEvent(vector<double>& vec){
    for (int i = 0; i < this->accfilters.size(); i++) {
        vec= this->accfilters.get(i).filter(vec);
        // cannot return here if null, because of time-dependent accfilters
    }
    
    // don't need to create an event if filtered away
    if (!vec.empty()) {
        // 	calculate the absolute value for the accelerationevent
        double absvalue = sqrt((vec[0] * vec[0]) +
                                    (vec[1] * vec[1]) + (vec[2] * vec[2]));
        //shared pointer aris sachiro
        shared_ptr<AccelerationEvent> w(new AccelerationEvent(vec[0], vec[1], vec[2], absvalue));
        for (int i = 0; i < this->accelerationlistener.size(); i++) {
            this->accelerationlistener.get(i).accelerationReceived(w);
        }
    }
}

void Device::fireButtonPressedEvent(int button){
//    System.out.println(Quantizer::PI);
    ButtonPressedEvent w = new ButtonPressedEvent(this, button);
    for (int i = 0; i < this->buttonlistener.size(); i++) {
        this.buttonlistener.get(i).buttonPressReceived(w);
    }
    
    if (w.isRecognitionInitEvent() || w.isTrainInitEvent()) {
        this.resetAccelerationFilters();
    }
}

void Device::fireMotionStopEvent(){
    
}
void Device::fireMotionStartEvent(){
    //TODO
}