//
//  GestureModel.hpp
//  WiiGee
//
//  Created by Nextep-3 on 22.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef GestureModel_hpp
#define GestureModel_hpp

#include <stdio.h>
#include "Quantizer.hpp"
#include "HMM.hpp"

class GestureModel{

public:
    GestureModel();
    void train(vector<Gesture>& trainsequence);
    double matches(Gesture &gesture);
    void printMap();
    void print();
    int getNumStates();
    int getNumObservations();
    double getDefaultProbability();
    void setDefaultProbability(vector<Gesture>& defsequence);
    void setDefaultProbability(double prob);
    Quantizer getQuantizer();
    void setQuantizer(Quantizer &q);
    HMM getHMM();
    void setHMM(HMM &hmm);
    
private:
    int numStates;
    int numObservations;
    Quantizer quantizer{8};//maybe pointer is a better idea!!
    HMM markovmodell{8, 14};
    double defaultprobability;
};

#endif /* GestureModel_hpp */
