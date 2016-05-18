//
//  ProcessingUnit.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ProcessingUnit_hpp
#define ProcessingUnit_hpp

#include "Classifier.hpp"
#include "GestureListener.hpp"
#include <vector>
#include "ButtonPressedEvent.hpp"
#include "ButtonReleasedEvent.hpp"
#include "AccelerationListener.hpp"
#include "ButtonListener.hpp"
#include <memory>

class ProcessingUnit: public AccelerationListener, public ButtonListener{
public:
    virtual ~ProcessingUnit() {}
    void addGestureListener(GestureListener* g);
    virtual void accelerationReceived(std::shared_ptr<AccelerationEvent> event) override = 0;
    virtual void buttonPressReceived(std::shared_ptr<ButtonPressedEvent> event)  override = 0;
    virtual void buttonReleaseReceived(std::shared_ptr<ButtonReleasedEvent> event) override = 0;
    
    virtual void loadGesture(string filename) = 0;
    virtual void saveGesture(int id, string filename) = 0;
    
    void reset();
    
protected:
    Classifier classifier;
    void fireGestureEvent(bool valid, int id, double probability);
    
private:
    GestureListener *gesturelistener;
};

#endif /* ProcessingUnit_hpp */
