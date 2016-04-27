//
//  DirectionalEqu	ivalenceFilter.cpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "DirectionalEquivalenceFilter.hpp"


void DirectionalEquivalenceFilter::reset() {
    this->sensivity=0.2;
    //zedmetia!!! tu ramem ar imushava komentars movxsni!!!
//    vector<double> zeroes{0.0, 0.0, 0.0};
//    setReference(zeroes);
}

vector<double>& DirectionalEquivalenceFilter::filterAlgorithm(vector<double>& vec) {
    
    if(vec[0] < reference[0] - this->sensivity ||
       vec[0] > reference[0] + this->sensivity ||
       vec[1] < reference[1] - this->sensivity ||
       vec[1] > reference[1] + this->sensivity ||
       vec[2] < reference[2] - this->sensivity ||
       vec[2] > reference[2] + this->sensivity) {
        setReference(vec);
        
    } else {
        vec.clear();
    }
    return vec;
}

void DirectionalEquivalenceFilter::setSensivity(double sensivity) {
    this->sensivity=sensivity;
}

double DirectionalEquivalenceFilter::getSensivity() {
    return this->sensivity;
}

void DirectionalEquivalenceFilter::setReference(vector<double>& vec){
    this->reference[0] = vec[0];
    this->reference[1] = vec[1];
    this->reference[2] = vec[2];
}