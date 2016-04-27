//
//  ButtonPressedEvent.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ButtonPressedEvent_hpp
#define ButtonPressedEvent_hpp

#include <stdio.h>
#include "Device.hpp"
#include "ActionStartEvent.hpp"

class ButtonPressedEvent: public ActionStartEvent {
    
public:
    // Fixed number values.
    static const int BUTTON_2 = 1;
    static const int BUTTON_1 = 2;
    static const int BUTTON_B = 3;
    static const int BUTTON_A = 4;
    static const int BUTTON_MINUS = 5;
    static const int BUTTON_HOME = 8;
    static const int BUTTON_LEFT = 9;
    static const int BUTTON_RIGHT = 10;
    static const int BUTTON_DOWN = 11;
    static const int BUTTON_UP = 12;
    static const int BUTTON_PLUS = 13;
    
    
    /**
     * Create a WiimoteButtonPressedEvent with the Wiimote source whose
     * Button has been pressed and the integer representation of the button.
     *
     * @param source
     * @param button
     */
    ButtonPressedEvent(Device& source, int button);
    int getButton();
    
private:
    int button;
};

#endif /* ButtonPressedEvent_hpp */
