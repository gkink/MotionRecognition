//
//  ButtonReleasedEvent.cpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "ButtonReleasedEvent.hpp"

ButtonReleasedEvent::ButtonReleasedEvent(int button) {
    this->button = button;
}

int ButtonReleasedEvent::getButton() {
    return this->button;
}