//
//  GestureEvent.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef GestureEvent_hpp
#define GestureEvent_hpp

class ProcessingUnit;

#include <stdio.h>


class GestureEvent {
    /** Create a GestureEvent
     *
     * @param source The Source, which detected the gesture.
     * @param id A gesture ID for identifying a gesture.
     * @param probability The Bayes-Classifier calculated probability.
     */
public:
    GestureEvent(ProcessingUnit* source, bool valid, int id, double probability);
    int getId();
    bool isValid();
    double getProbability();
    ProcessingUnit* getSource();
    
private:
    int id;
    bool valid;
    double probability;
    ProcessingUnit* analyzer;
};


#endif /* GestureEvent_hpp */
