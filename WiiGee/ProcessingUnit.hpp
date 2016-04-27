//
//  ProcessingUnit.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ProcessingUnit_hpp
#define ProcessingUnit_hpp

#include <stdio.h>
#include "Classifier.hpp"
#include "GestureListener.hpp"
#include <vector>
#include "ButtonPressedEvent.hpp"
#include "ButtonReleasedEvent.hpp"
#include "MotionStartEvent.hpp"
#include "MotionStopEvent.hpp"
#include "AccelerationListener.hpp"

class ProcessingUnit: public AccelerationListener, public ButtonListener{
public:
    ProcessingUnit();
    virtual ~ProcessingUnit() {};
    void addGestureListener(GestureListener g);
    virtual void accelerationReceived(AccelerationEvent event) = 0;
    virtual void buttonPressReceived(ButtonPressedEvent event) = 0;
    virtual void buttonReleaseReceived(ButtonReleasedEvent event) = 0;
    virtual void motionStartReceived(MotionStartEvent event) = 0;
    virtual void motionStopReceived(MotionStopEvent event) = 0;
    
    virtual void accelerationReceived(AccelerationEvent event) = 0;
    virtual void motionStartReceived(MotionStartEvent event) = 0;
    virtual void motionStopReceived(MotionStopEvent event) = 0;
    
    virtual void buttonPressReceived(ButtonPressedEvent event) = 0;
    virtual void buttonReleaseReceived(ButtonReleasedEvent event) = 0;
    
    void reset();
    
protected:
    Classifier classifier;
    void fireGestureEvent(bool valid, int id, double probability);
    
private:
    vector<GestureListener> gesturelistener;
};

#endif /* ProcessingUnit_hpp */
