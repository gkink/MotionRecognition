//
//  ButtonReleasedEvent.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ButtonReleasedEvent_hpp
#define ButtonReleasedEvent_hpp

#include <stdio.h>
#include "Device.hpp"
#include "ActionStopEvent.hpp"

class ButtonReleasedEvent: public ActionStopEvent {
    
public:
    ButtonReleasedEvent(Device source, int button);
    int getButton();
    
private:
    int button;
};

#endif /* ButtonReleasedEvent_hpp */
