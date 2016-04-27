//
//  ProcessingUnit.cpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "ProcessingUnit.hpp"

void ProcessingUnit::addGestureListener(GestureListener g){
    this->gesturelistener.push_back(g);
}

void ProcessingUnit::reset() {
    if (this->classifier.getCountOfGestures() > 0) {
        this->classifier.clear();
//        Log.write("### Model reset ###");
    } else {
//        Log.write("There doesn't exist any data to reset.");
    }
}
