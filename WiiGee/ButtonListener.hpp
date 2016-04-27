//
//  ButtonListener.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ButtonListener_hpp
#define ButtonListener_hpp

#include "ButtonReleasedEvent.hpp"
#include "ButtonPressedEvent.hpp"

class ButtonListener {
   
public:
    
    /**
     * This method would be called if a Device button has been pressed.
     *
     * @param event The button representation as an event.
     */
    virtual void buttonPressReceived(ButtonPressedEvent event) = 0;
    
    /**
     * This method would be called if a Device button has been released.
     *
     * @param event This is actually a meta-event NOT containing which button
     * has been released.
     */
    virtual void buttonReleaseReceived(ButtonReleasedEvent event) = 0;
};

#endif /* ButtonListener_h */
