//
//  Quantizer.cpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "Quantizer.hpp"
#include "AccelerationEvent.hpp"
#include <math.h>
#include <cfloat>
#include <iostream>
#include <string>

using namespace std;

Quantizer::Quantizer(int numSt): numStates{numSt}, maptrained{false} {
    this->map.resize(MAP_NUMBER_OF_ROWS, vector<double>(MAP_NUMBER_OF_COLUMNS));
}


void Quantizer::trainCentroids(Gesture &gesture){
    vector<AccelerationEvent> data = gesture.getData();
    double pi = PI;
    this->radius = (gesture.getMaxAcceleration() + gesture.getMinAcceleration()) / 2;
    //log write is needded!!!!!!!!!!(see java code!!!)
    
    if (!this->maptrained){
        this->maptrained = true;
        this->map[0] = {this->radius, 0.0, 0.0};
        this->map[1] = { cos(pi / 4) * this->radius, 0.0, sin(pi / 4) * this->radius };
        this->map[2] = { 0.0, 0.0, this->radius };
        this->map[3] = { cos(pi * 3 / 4) * this->radius, 0.0, sin(pi * 3 / 4) * this->radius };
        this->map[4] = { -this->radius, 0.0, 0.0 };
        this->map[5] = { cos(pi * 5 / 4) * this->radius, 0.0, sin(pi * 5 / 4) * this->radius };
        this->map[6] = { 0.0, 0.0, -this->radius };
        this->map[7] = { cos(pi * 7 / 4) * this->radius, 0.0, sin(pi * 7 / 4) * this->radius };
        this->map[8] = { 0.0, this->radius, 0.0 };
        this->map[9] = { 0.0, cos(pi / 4) * this->radius, sin(pi / 4) * this->radius };
        this->map[10] = { 0.0, cos(pi * 3 / 4) * this->radius, sin(pi * 3 / 4) * this->radius };
        this->map[11] = { 0.0, -this->radius, 0.0 };
        this->map[12] = { 0.0, cos(pi * 5 / 4) * this->radius, sin(pi * 5 / 4) * this->radius };
        this->map[13] = { 0.0, cos(pi * 7 / 4) * this->radius, sin(pi * 7 / 4) * this->radius };
    }
    
    vector<vector<int>> g_alt(MAP_NUMBER_OF_ROWS, vector<int>(data.size()));
    vector<vector<int>> g(MAP_NUMBER_OF_ROWS, vector<int>(data.size()));
    
    do {
        // Derive new Groups...
        g_alt = g;
        g = this->deriveGroups(gesture);
        
        // calculate new centeroids
        for (int i = 0; i < this->MAP_NUMBER_OF_ROWS; i++) {
            double zaehlerX = 0;
            double zaehlerY = 0;
            double zaehlerZ = 0;
            int nenner = 0;
            for (int j = 0; j < data.size(); j++) {
                if (g[i][j] == 1) {
                    zaehlerX += data[j].getX();
                    zaehlerY += data[j].getY();
                    zaehlerZ += data[j].getZ();
                    nenner++;
                }
            }
            if (nenner > 1) { // nur wenn der nenner>0 oder >1??? ist muss
                // was
                // geaendert werden
                // Log.write("Setze neuen Centeroid!");
                this->map[i] = {(zaehlerX / (double) nenner),
                    (zaehlerY / (double) nenner),
                    (zaehlerZ / (double) nenner) };
                // Log.write("Centeroid: "+i+": "+newcenteroid[0]+":"+newcenteroid[1]);
            }
        } // new centeroids
        
    } while (!equalArray(g_alt, g));
}


vector<vector<int>> Quantizer::deriveGroups(Gesture &gesture) {
    
    vector<AccelerationEvent> data = gesture.getData();
    vector<vector<int>> groups(MAP_NUMBER_OF_ROWS, vector<int>(data.size()));
    
    // Calculate cartesian distance
    vector<vector<double>> d(map.size(), vector<double>(data.size()));
    vector<double> curr(3);
    vector<double> vect(3);
    
    for (int i = 0; i < map.size(); i++) { // zeilen
        vector<double> ref = this->map[i];
        for (int j = 0; j < data.size(); j++) { // spalten
            
            curr[0] = data[j].getX();
            curr[1] = data[j].getY();
            curr[2] = data[j].getZ();
            
            vect[0] = ref[0] - curr[0];
            vect[1] = ref[1] - curr[1];
            vect[2] = ref[2] - curr[2];
            d[i][j] = sqrt((vect[0] * vect[0])
                                + (vect[1] * vect[1]) + (vect[2] * vect[2]));
        }
    }
    
    // look, to which group a value belongs
    for (int j = 0; j < data.size(); j++) {
        double smallest = DBL_MAX;
        int row = 0;
        for (int i = 0; i < MAP_NUMBER_OF_ROWS; i++) {
            if (d[i][j] < smallest) {
                smallest = d[i][j];
                row = i;
            }
            groups[i][j] = 0;
        }
        groups[row][j] = 1; // guppe gesetzt
    }
    
    return groups;
}


vector<int> Quantizer::getObservationSequence(Gesture &gesture){
    
    vector<vector<int>> groups = this->deriveGroups(gesture);
    vector<int> sequence;
    
    for (int j = 0; j < groups[0].size(); j++) { // spalten
        for (int i = 0; i < groups.size(); i++) { // zeilen
            if (groups[i][j] == 1) {
                // Log.write(" "+ i);
                sequence.push_back(i);
                break;
            }
        }
    }
    
    // die sequenz darf nicht zu kurz sein... mindestens so lang
    // wie die anzahl der zustände. weil sonst die formeln nicht klappen.
    // english: this is very dirty! it have to be here because if not
    // too short sequences would cause an error. i've to think about a
    // better resolution than copying the old value a few time.
    while (sequence.size() < this->numStates) {
        sequence.push_back((sequence[(sequence.size() - 1)]));
        // Log.write(" "+sequence.elementAt(sequence.size()-1));
    }
    
    // Log.write("");
    
    vector<int> out;
    for (int i = 0; i < sequence.size(); i++) {
        out[i] = sequence[i];
    }
    
    return out;
}


void Quantizer::printMap(){
    cout << "centroids" << endl;
    for (int i = 0; i < this->map.size(); i++) {
        cout << to_string(i) + ". :" + to_string(this->map[i][0]) + ":" + to_string(this->map[i][1]) + ":" + to_string(this->map[i][2]) << endl;
    }
}


bool Quantizer::equalArray(vector<vector<int> > &one, vector<vector<int> > &second){
    
    for (int i = 0; i < one.size(); i++) {
        for (int j = 0; j < one[i].size(); j++) {
            if (!(one[i][j] == second[i][j])) {
                return false;
            }
        }
    }
    return true;
}


double Quantizer::getRadius(){
    return this->radius;
}


vector<vector<double>>& Quantizer::getHashMap(){
    return this->map;
}


void Quantizer::setUpManually(vector<vector<double> > &map, double radius){
    this->map = map;
    this->radius = radius;
}