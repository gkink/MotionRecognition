//
//  ActionStartEvent.hpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ActionStartEvent_hpp
#define ActionStartEvent_hpp

#include <stdio.h>

class ActionStartEvent {
    
protected:
    bool trainbutton;
    bool recognitionbutton;
    bool closegesturebutton;

public:
    virtual bool isRecognitionInitEvent();
    virtual bool isTrainInitEvent();
    virtual bool isCloseGestureInitEvent();
};

#endif /* ActionStartEvent_hpp */
