//
//  TriggeredProcessingUnit.cpp
//  WiiGee
//
//  Created by Nextep-3 on 27.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "TriggeredProcessingUnit.hpp"

TriggeredProcessingUnit::TriggeredProcessingUnit(){
    this->learning = false;
    this->analyzing = false;
}

void TriggeredProcessingUnit::accelerationReceived(std::shared_ptr<AccelerationEvent> event){
    if(this->learning || this->analyzing) {
        this->current->add(event); // add event to gesture
    }
}

//
//void TriggeredProcessingUnit::accelerationReceived(AccelerationEvent event) {
//    //fdgsf
//}
//void TriggeredProcessingUnit::buttonPressReceived(ButtonPressedEvent event){}
//void TriggeredProcessingUnit::buttonReleaseReceived(ButtonReleasedEvent event){}
//void TriggeredProcessingUnit::motionStartReceived(MotionStartEvent event){}
//void TriggeredProcessingUnit::motionStopReceived(MotionStopEvent event){}
//
//void TriggeredProcessingUnit::loadGesture(string filename){}
//void TriggeredProcessingUnit::saveGesture(int id, string filename){}