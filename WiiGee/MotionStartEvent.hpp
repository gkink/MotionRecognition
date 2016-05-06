//
//  MotionStartEvent.hpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef MotionStartEvent_hpp
#define MotionStartEvent_hpp

class Device;

#include "ActionStartEvent.hpp"

class MotionStartEvent: public ActionStartEvent {
    
public:    
    MotionStartEvent(Device* source);
    bool isTrainInitEvent();
    bool isCloseGestureInitEvent();
    bool isRecognitionInitEvent();
};

#endif /* MotionStartEvent_hpp */
