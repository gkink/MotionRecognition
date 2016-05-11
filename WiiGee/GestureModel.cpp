//
//  GestureModel.cpp
//  WiiGee
//
//  Created by Nextep-3 on 22.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "GestureModel.hpp"

GestureModel::GestureModel(){
    this->numStates = 8;
    this->numObservations = 14;
}

void GestureModel::train(vector<shared_ptr<Gesture>> trainsequence) {
    // summarize all vectors from the different gestures in one
    // gesture called sum.
    double maxacc = 0;
    double minacc = 0;
    shared_ptr<Gesture> sum(new Gesture());
    
    for(int i = 0; i < trainsequence.size(); i++) {
        vector<shared_ptr<AccelerationEvent>> t = trainsequence[i]->getData();
        
        // add the max and min acceleration, we later get the average
        maxacc+=trainsequence[i]->getMaxAcceleration();
        minacc+=trainsequence[i]->getMinAcceleration();
        
        // transfer every single accelerationevent of each gesture to
        // the new gesture sum
        for(int j=0; j<trainsequence[i]->getData().size(); j++) {
            sum->add(t[j]);
        }
        
    }
    
    // get the average and set it to the sum gesture
    sum->setMaxAndMinAcceleration(maxacc/trainsequence.size(), minacc/trainsequence.size());
    
    // train the centeroids of the quantizer with this master gesture sum.
    this->quantizer.trainCentroids(sum);
    
    // convert gesture vector to a sequence of discrete values
    vector<vector<int>> seqs;
    for(int i=0; i<trainsequence.size(); i++) {
        seqs.push_back((this->quantizer.getObservationSequence(trainsequence[i])));
    }
    
    // train the markov model with this derived discrete sequences
    this->markovmodell.train(seqs);
    
    // set the default probability for use with the bayes classifier
    this->setDefaultProbability(trainsequence);
}

double GestureModel::matches(shared_ptr<Gesture> gesture) {
    vector<int> sequence = quantizer.getObservationSequence(gesture);
    return this->markovmodell.getProbability(sequence);
}

void GestureModel::printMap(){
    //log write is omitted
    this->quantizer.printMap();
}

void GestureModel::print(){
    //log write is omitted
    this->markovmodell.print();
    //log write is omitted
    this->quantizer.printMap();
}

int GestureModel::getNumStates(){
    return this->numStates;
}

int GestureModel::getNumObservations(){
    return this->numObservations;
}

double GestureModel::getDefaultProbability(){
    return this->defaultprobability;
}

void GestureModel::setDefaultProbability(vector<shared_ptr<Gesture>>& defsequence){
    double prob = 0;
    for(int i=0; i<defsequence.size(); i++) {
        prob+=this->matches(defsequence[i]);
    }
    
    this->defaultprobability=(prob)/defsequence.size();
}

void GestureModel::setDefaultProbability(double prob){
    this->defaultprobability = prob;
    //log write is omitted
}

Quantizer GestureModel::getQuantizer(){
    return this->quantizer;
}

void GestureModel::setQuantizer(Quantizer &q){
    this->quantizer = q;
}

HMM GestureModel::getHMM(){
    return this->markovmodell;
}

void GestureModel::setHMM(HMM &hmm){
    this->markovmodell = hmm;
}