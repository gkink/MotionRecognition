//
//  GestureEvent_cpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "GestureEvent.hpp"

GestureEvent::GestureEvent(ProcessingUnit source, bool valid, int id, double probability) {
    this->analyzer = source;
    this->valid = valid;
    this->id = id;
    this->probability = probability;
}
    
int GestureEvent::getId() {
    return this->id;
}

bool GestureEvent::isValid() {
    return this->valid;
}

double GestureEvent::getProbability() {
    return this->probability;
}

ProcessingUnit GestureEvent::getSource() {
    return this->analyzer;
}