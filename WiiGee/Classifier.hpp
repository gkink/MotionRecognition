//
//  Classifier.hpp
//  WiiGee
//
//  Created by Nextep-3 on 25.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef Classifier_hpp
#define Classifier_hpp

#include <stdio.h>
#include <vector>
#include "GestureModel.hpp"

using namespace std;

class Classifier{
    
public:
    Classifier();
    int classifyGesture(Gesture g);
    double getLastProbability();
    void addGestureModel(GestureModel gm);
    GestureModel getGestureModel(int id);
    vector<GestureModel> getGestureModels();
    size_t getCountOfGestures();
    void clear();
    
private:
    vector<GestureModel> gesturemodel;
    double lastprob;
    
};

#endif /* Classifier_hpp */
