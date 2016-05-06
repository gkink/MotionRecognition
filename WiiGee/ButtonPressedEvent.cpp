//
//  ButtonPressedEvent.cpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "ButtonPressedEvent.hpp"
#include "Device.hpp"

ButtonPressedEvent::ButtonPressedEvent(Device* source, int button) {
        this->button = button;
        
        if(source->getRecognitionButton() == button) {
            this->recognitionbutton = true;
        } else if(source->getTrainButton() == button) {
            this->trainbutton = true;
        } else if(source->getCloseGestureButton() == button) {
            this->closegesturebutton = true;
        }
    }
    
int ButtonPressedEvent::getButton() {
    return this->button;
}