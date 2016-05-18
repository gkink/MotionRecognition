//
//  GeneralDevice.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "GeneralDevice.hpp"
#include "IdleStateFilter.hpp"
#include "DirectionalEquivalenceFilter.hpp"
#include "ButtonListener.hpp"
#include <math.h>
#include "Quantizer.hpp"

GeneralDevice::GeneralDevice(bool autofiltering){
    if (autofiltering) {
        this->addAccelerationFilter(unique_ptr<IdleStateFilter>( new IdleStateFilter()));
        this->addAccelerationFilter(unique_ptr<DirectionalEquivalenceFilter>(new DirectionalEquivalenceFilter()));
    }
    this->addAccelerationListener(this->processingunit);
    this->addButtonListener(this->processingunit);
}

void GeneralDevice::addAccelerationFilter(unique_ptr<Filter> filter){
    this->accfilters.push_back(std::move(filter));
}

void GeneralDevice::addAccelerationListener(shared_ptr<AccelerationListener> listener){
    this->accelerationlistener.push_back(listener);
}

void GeneralDevice::resetAccelerationFilters(){
    for (int i = 0; i < this->accfilters.size(); i++) {
        this->accfilters.at(i).reset();
    }
}

void GeneralDevice::addGestureListener(GestureListener* listener){
    this->processingunit->addGestureListener(listener);
}

void GeneralDevice::addButtonListener(shared_ptr<ButtonListener> listener){
    this->buttonlistener.push_back(std::move(listener));
}

void GeneralDevice::fireAccelerationEvent(vector<double>& vec){
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

void GeneralDevice::fireButtonPressedEvent(int button){
//    System.out.println(Quantizer::PI);
    
    shared_ptr<ButtonPressedEvent> w(new ButtonPressedEvent(this, button));
    for (int i = 0; i < this->buttonlistener.size(); i++) {
        this->buttonlistener.at(i)->buttonPressReceived(w);
    }
    
    if (w->isRecognitionInitEvent() || w->isTrainInitEvent()) {
        this->resetAccelerationFilters();
    }
}

void GeneralDevice::fireButtonReleasedEvent(int button){
    shared_ptr<ButtonReleasedEvent> w (new ButtonReleasedEvent(button));
    for (int i = 0; i < this->buttonlistener.size(); i++) {
        this->buttonlistener.at(i)->buttonReleaseReceived(w);
    }
}