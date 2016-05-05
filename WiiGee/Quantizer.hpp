//
//  Quantizer.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef Quantizer_hpp
#define Quantizer_hpp

#include "Gesture.hpp"
#include <vector>

using namespace std;

class Quantizer{
    
private:
    static const int MAP_NUMBER_OF_ROWS = 14;
    static const int MAP_NUMBER_OF_COLUMNS = 3;
    
    double radius;
    int numStates;
    vector<vector<double> > map;
    bool maptrained;
    
    bool equalArray(vector<vector<int>> &one, vector<vector<int>> &second);
    
public:
    constexpr static const double PI = 3.141592653589793;
    Quantizer(int numSt);
    void trainCentroids(Gesture &gesture);
    vector<vector<int>> deriveGroups(Gesture &gesture);
    vector<int> getObservationSequence(Gesture &gesture);
    void printMap();
    double getRadius();
    vector<vector<double>>& getHashMap();
    void setUpManually(vector<vector<double>>& map, double radius);
};

#endif /* Quantizer_hpp */
