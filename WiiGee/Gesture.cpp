//
//  Gesture.cpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "Gesture.hpp"
#include <math.h>
#include <cfloat>
#include <cmath>

Gesture::Gesture(shared_ptr<Gesture> original){
    vector<shared_ptr<AccelerationEvent>> origin = original->getData();
    for (int i = 0; i < origin.size(); i++){
        this->data.push_back(origin[i]);
    }
}

void Gesture::add(shared_ptr<AccelerationEvent> event){
    this->data.push_back(event);
}

shared_ptr<AccelerationEvent> Gesture::getLastData(){
    return this->data[this->data.size() - 1];
}

vector<shared_ptr<AccelerationEvent>> &Gesture::getData(){
    return this->data;
}

void Gesture::removeFirstData(){
    this->data.erase(data.begin());
}

size_t Gesture::getCountOfData(){
    return this->data.size();
}

void Gesture::setMaxAndMinAcceleration(double max, double min){
    this->maxacc = max;
    this->minacc = min;
    this->minmaxmanual = true;
}

double Gesture::getMaxAcceleration(){
    if(!this->minmaxmanual) {
        double maxacc = DBL_MIN;
        for(int i=0; i<this->data.size(); i++) {
            if(abs(this->data[i]->getX()) > maxacc) {
                maxacc=abs(this->data[i]->getX());
            }
            if(abs(this->data[i]->getY()) > maxacc) {
                maxacc=abs(this->data[i]->getY());
            }
            if(abs(this->data[i]->getZ()) > maxacc) {
                maxacc=abs(this->data[i]->getZ());
            }
        }
        return maxacc;
    } else {
        return this->maxacc;
    }
}

double Gesture::getMinAcceleration(){
    if(!this->minmaxmanual) {
        double minacc = DBL_MAX;
        for(int i=0; i<this->data.size(); i++) {
            if(abs(this->data[i]->getX()) < minacc) {
                minacc=abs(this->data[i]->getX());
            }
            if(abs(this->data[i]->getY()) < minacc) {
                minacc=abs(this->data[i]->getY());
            }
            if(abs(this->data[i]->getZ()) < minacc) {
                minacc=abs(this->data[i]->getZ());
            }
        }
        return minacc;
    } else {
        return this->minacc;
    }
}