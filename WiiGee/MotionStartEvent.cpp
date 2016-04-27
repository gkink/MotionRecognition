//
//  MotionStartEvent.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "MotionStartEvent.hpp"

MotionStartEvent::MotionStartEvent(Device source) {
    
    if (source.getRecognitionButton() == Device::MOTION) {
        this->recognitionbutton = true;
    } else if(source.getTrainButton() == Device::MOTION) {
        this->trainbutton = true;
    } else if(source.getCloseGestureButton() == Device::MOTION) {
        this->closegesturebutton = true;
    }
}

bool MotionStartEvent::isTrainInitEvent() {
    return this->trainbutton;
}

bool MotionStartEvent::isCloseGestureInitEvent() {
    return this->closegesturebutton;
}

bool MotionStartEvent::isRecognitionInitEvent() {
    return this->recognitionbutton;
}
