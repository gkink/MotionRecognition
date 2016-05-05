//
//  TriggeredProcessingUnit.hpp
//  WiiGee
//
//  Created by Nextep-3 on 27.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef TriggeredProcessingUnit_hpp
#define TriggeredProcessingUnit_hpp

#include <stdio.h>
#include "ProcessingUnit.hpp"

class TriggeredProcessingUnit: public ProcessingUnit{
    ~TriggeredProcessingUnit() {};
    virtual void accelerationReceived(AccelerationEvent event);
    virtual void buttonPressReceived(ButtonPressedEvent event);
    virtual void buttonReleaseReceived(ButtonReleasedEvent event);
    virtual void motionStartReceived(MotionStartEvent event);
    virtual void motionStopReceived(MotionStopEvent event);
    
    virtual void loadGesture(string filename);
    virtual void saveGesture(int id, string filename);
    
};

#endif /* TriggeredProcessingUnit_hpp */
