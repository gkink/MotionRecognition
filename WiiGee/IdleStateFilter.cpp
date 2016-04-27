//
//  IdleStateFilter.cpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "IdleStateFilter.hpp"
#include <math.h>


void IdleStateFilter::reset(){
    // not needed
}


vector<double>& IdleStateFilter::filterAlgorithm(vector<double>& vec) {
    
    double absvalue = sqrt((vec[0]*vec[0])+
                                (vec[1]*vec[1])+(vec[2]*vec[2]));
    
    if(absvalue > 1 + this->sensivity ||
       absvalue < 1 - this->sensivity) {
    } else {
        vec.clear();
    }
    return vec;
}


void IdleStateFilter::setSensivity(double sensivity) {
    this->sensivity = sensivity;
}


double IdleStateFilter::getSensivity() {
    return this->sensivity;
}
