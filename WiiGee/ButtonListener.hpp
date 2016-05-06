//
//  ButtonListener.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef ButtonListener_hpp
#define ButtonListener_hpp

class ButtonPressedEvent;

#include "ButtonReleasedEvent.hpp"
#include <memory>

class ButtonListener {
   
public:
    
    /**
     * This method would be called if a Device button has been pressed.
     *
     * @param event The button representation as an event.
     */
    virtual void buttonPressReceived(std::shared_ptr<ButtonPressedEvent> event) = 0;
    
    /**
     * This method would be called if a Device button has been released.
     *
     * @param event This is actually a meta-event NOT containing which button
     * has been released.
     */
    virtual void buttonReleaseReceived(std::shared_ptr<ButtonReleasedEvent> event) = 0;
};

#endif /* ButtonListener_h */
