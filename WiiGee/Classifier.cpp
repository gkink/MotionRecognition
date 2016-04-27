//
//  Classifier.cpp
//  WiiGee
//
//  Created by Nextep-3 on 25.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "Classifier.hpp"
#include <float.h>

Classifier::Classifier(){
    this->lastprob = 0.0;
}

int Classifier::classifyGesture(Gesture g) {
    //Log.write("Recognizing gesture...");
    
    // Wert im Nenner berechnen, nach Bayes
    double sum = 0;
    for(int i=0; i<this->gesturemodel.size(); i++) {
        sum+=this->gesturemodel[i].getDefaultProbability()*
        this->gesturemodel[i].matches(g);
    }
    
    int recognized = -1; // which gesture has been recognized
    double recogprob = INT_MIN; // probability of this gesture
    double probgesture = 0; // temporal value for bayes algorithm
    double probmodel = 0; // temporal value for bayes algorithm
    for(int i=0; i<this->gesturemodel.size(); i++) {
        //this.gesturemodel.elementAt(i).print(); // Debug
        double tmpgesture = this->gesturemodel[i].matches(g);
        double tmpmodel = this->gesturemodel[i].getDefaultProbability();
        
        if(((tmpmodel*tmpgesture)/sum)>recogprob) {
            probgesture=tmpgesture;
            probmodel=tmpmodel;
            recogprob=((tmpmodel*tmpgesture)/sum);
            recognized=i;
        }
    }
    
    // a gesture could be recognized
    if(recogprob>0 && probmodel>0 && probgesture>0 && sum>0) {
        this->lastprob=recogprob;
        return recognized;
    } else {
        // no gesture could be recognized
        return -1;
    }
    
}

double Classifier::getLastProbability(){
    return this->lastprob;
}

void Classifier::addGestureModel(GestureModel gm){
    this->gesturemodel.push_back(gm);
}

GestureModel Classifier::getGestureModel(int id){
    return this->gesturemodel[id];
}

vector<GestureModel> Classifier::getGestureModels(){
    return this->gesturemodel;
}

size_t Classifier::getCountOfGestures(){
    return this->gesturemodel.size();
}

void Classifier::clear(){
    this->gesturemodel.clear();
}