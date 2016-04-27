//
//  HMM.hpp
//  WiiGee
//
//  Created by Nextep-3 on 22.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef HMM_hpp
#define HMM_hpp

#include <stdio.h>
#include <vector>

using namespace std;

class HMM{
    
public:
    HMM(int numStates, int numObservations);
    void reset();
    void train(vector<vector<int>>& trainsequence);
    double getProbability(vector<int>& o);
    void print();
    vector<double> getPi();
    void setPi(vector<double>& pi);
    vector<vector<double>> getA();
    void setA(vector<vector<double>>& a);
    vector<vector<double>> getB();
    void setB(vector<vector<double>>& b);
    
protected:
    int numStates;
    int numObservations;
    vector<double> pi;
    vector<vector<double>> a;
    vector<vector<double>> b;
    
    vector<vector<double>> forwardProc(vector<int>& o);
    vector<vector<double>> backwardProc(vector<int>& o);
    
};

#endif /* HMM_hpp */
