//
//  Device.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "Device.hpp"
#include "IdleStateFilter.hpp"
#include "MotionDetectFilter.hpp"
#include "DirectionalEquivalenceFilter.hpp"
#include "ButtonListener.hpp"
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
    this->accfilters.push_back(std::move(filter));
}

void Device::addAccelerationListener(shared_ptr<AccelerationListener> listener){
    this->accelerationlistener.push_back(listener);
}

void Device::resetAccelerationFilters(){
    for (int i = 0; i < this->accfilters.size(); i++) {
        this->accfilters.at(i).reset();
    }
}

void Device::addGestureListener(unique_ptr<GestureListener> listener){
    this->processingunit->addGestureListener(std::move(listener));
}

void Device::addButtonListener(shared_ptr<ButtonListener> listener){
    this->buttonlistener.push_back(std::move(listener));
}

void Device::fireAccelerationEvent(vector<double>& vec){
    for (int i = 0; i < this->accfilters.size(); i++) {
        vec= this->accfilters.at(i)->filter(vec);
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
            this->accelerationlistener.at(i)->accelerationReceived(w);
        }
    }
}

void Device::fireButtonPressedEvent(int button){
//    System.out.println(Quantizer::PI);
    
    shared_ptr<ButtonPressedEvent> w(new ButtonPressedEvent(this, button));
    for (int i = 0; i < this->buttonlistener.size(); i++) {
        this->buttonlistener.at(i)->buttonPressReceived(w);
    }
    
    if (w->isRecognitionInitEvent() || w->isTrainInitEvent()) {
        this->resetAccelerationFilters();
    }
}

void Device::fireButtonReleasedEvent(int button){
    shared_ptr<ButtonReleasedEvent> w (new ButtonReleasedEvent(button));
    for (int i = 0; i < this->buttonlistener.size(); i++) {
        this->buttonlistener.at(i)->buttonReleaseReceived(w);
    }
}

void Device::fireMotionStopEvent(){
    shared_ptr<MotionStopEvent> w(new MotionStopEvent());
    for (int i = 0; i < this->accelerationlistener.size(); i++) {
        this->accelerationlistener.at(i)->motionStopReceived(w);
    }
}
void Device::fireMotionStartEvent(){
    shared_ptr<MotionStartEvent> w (new MotionStartEvent(this));
    for (int i = 0; i < this->accelerationlistener.size(); i++) {
        this->accelerationlistener.at(i)->motionStartReceived(w);
    }
}