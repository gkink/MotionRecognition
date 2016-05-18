//
//  TriggeredProcessingUnit.hpp
//  WiiGee
//
//  Created by Nextep-3 on 27.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef TriggeredProcessingUnit_hpp
#define TriggeredProcessingUnit_hpp

#include "ProcessingUnit.hpp"
#include <string>

using namespace std;

class TriggeredProcessingUnit: public ProcessingUnit{
    
public:
    TriggeredProcessingUnit();
    ~TriggeredProcessingUnit() {};
    virtual void accelerationReceived(std::shared_ptr<AccelerationEvent> event) override;
    virtual void buttonPressReceived(std::shared_ptr<ButtonPressedEvent> event) override;
    virtual void buttonReleaseReceived(std::shared_ptr<ButtonReleasedEvent> event) override;
    
    void handleStartEvent(shared_ptr<ActionStartEvent> event);
    void handleStopEvent(shared_ptr<ActionStopEvent> event);
        
    virtual void loadGesture(string filename) override;
    virtual void saveGesture(int id, string filename) override;
    
private:
    shared_ptr<Gesture> current{new Gesture()};
    vector<shared_ptr<Gesture>> trainsequence;
    bool learning;
    bool analyzing;
    
};

#endif /* TriggeredProcessingUnit_hpp */
