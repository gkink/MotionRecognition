//
//  HMM.cpp
//  WiiGee
//
//  Created by Nextep-3 on 22.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "HMM.hpp"

HMM::HMM(int numStates, int numObservations){
    this->numStates = numStates;
    this->numObservations = numObservations;
    this->pi.resize(numStates);
    this->a.resize(numStates, vector<double>(numStates));
    this->b.resize(numStates, vector<double>(numObservations));
    this->reset();
}

void HMM::reset(){
    int jumplimit = 2;
    
    // set startup probability
    pi[0] = 1;
    for(int i=1; i<numStates; i++) {
        pi[i] = 0;
    }
    
    // set state change probabilities in the left-to-right version
    // NOTE: i now that this is dirty and very static. :)
    for(int i=0; i<numStates; i++) {
        for(int j=0; j<numStates; j++) {
            if(i==numStates-1 && j==numStates-1) { // last row
                a[i][j] = 1.0;
            } else if(i==numStates-2 && j==numStates-2) { // next to last row
                a[i][j] = 0.5;
            } else if(i==numStates-2 && j==numStates-1) { // next to last row
                a[i][j] = 0.5;
            } else if(i<=j && i>j-jumplimit-1) {
                a[i][j] = 1.0/(jumplimit+1);
            } else {
                a[i][j] = 0.0;
            }
        }
    }
    
    
    // emission probability
    for(int i=0; i<numStates; i++) {
        for(int j=0; j<numObservations; j++) {
            b[i][j] = 1.0/(double)numObservations;
        }
    }
}

void HMM::train(vector<vector<int>>& trainsequence){
    
    vector<vector<double>> a_new(a.size(), vector<double>(a.size()));
    vector<vector<double>> b_new(b.size(), vector<double>(b.size()));
    // re calculate state change probability a
    for(int i=0; i<a.size(); i++) {
        for(int j=0; j<a[i].size(); j++) {
            double zaehler=0;
            double nenner=0;
            
            for(int k=0; k<trainsequence.size(); k++) {
                vector<int> sequence = trainsequence[k];
                
                vector<vector<double>> fwd = this->forwardProc(sequence);
                vector<vector<double>> bwd = this->backwardProc(sequence);
                double prob = this->getProbability(sequence);
                
                double zaehler_innersum=0;
                double nenner_innersum=0;
                
                
                for(int t=0; t<sequence.size()-1; t++) {
                    zaehler_innersum+=fwd[i][t]*a[i][j]*b[j][sequence[t+1]]*bwd[j][t+1];
                    nenner_innersum+=fwd[i][t]*bwd[i][t];
                }
                zaehler+=(1/prob)*zaehler_innersum;
                nenner+=(1/prob)*nenner_innersum;
            } // k
            
            a_new[i][j] = zaehler/nenner;
        } // j
    } // i
    
    // re calculate emission probability b
    for(int i=0; i<b.size(); i++) { // zustaende
        for(int j=0; j<b[i].size(); j++) {	// symbole
            double zaehler=0;
            double nenner=0;
            
            for(int k=0; k<trainsequence.size(); k++) {
                vector<int> sequence = trainsequence[k];
                
                vector<vector<double>> fwd = this->forwardProc(sequence);
                vector<vector<double>> bwd = this->backwardProc(sequence);
                double prob = this->getProbability(sequence);
                
                double zaehler_innersum=0;
                double nenner_innersum=0;
                
                
                for(int t=0; t<sequence.size()-1; t++) {
                    if(sequence[t]==j) {
                        zaehler_innersum+=fwd[i][t]*bwd[i][t];
                    }
                    nenner_innersum+=fwd[i][t]*bwd[i][t];
                }
                zaehler+=(1/prob)*zaehler_innersum;
                nenner+=(1/prob)*nenner_innersum;
            } // k
            
            b_new[i][j] = zaehler/nenner;
        } // j
    } // i
    
    this->a=a_new;
    this->b=b_new;
}

vector<vector<double>> HMM::forwardProc(vector<int>& o){
    
    vector<vector<double>> f(numStates, vector<double>(o.size()));
    for (int l = 0; l < f.size(); l++) {
        f[l][0] = pi[l] * b[l][o[0]];
    }
    for (int i = 1; i < o.size(); i++) {
        for (int k = 0; k < f.size(); k++) {
            double sum = 0;
            for (int l = 0; l < numStates; l++) {
                sum += f[l][i-1] * a[l][k];
            }
            f[k][i] = sum * b[k][o[i]];
        }
    }
    return f;
}

double HMM::getProbability(vector<int>& o){
    double prob = 0.0;
    vector<vector<double>> forward = this->forwardProc(o);
    //	add probabilities
    for (int i = 0; i < forward.size(); i++) { // for every state
        prob += forward[i][forward[i].size() - 1];
    }
    return prob;
}

vector<vector<double>> HMM::backwardProc(vector<int>& o){
    int T = static_cast<int>(o.size());
    vector<vector<double>> bwd(numStates, vector<double>(T));
    /* Basisfall */
    for (int i = 0; i < numStates; i++)
        bwd[i][T - 1] = 1;
    /* Induktion */
    for (int t = T - 2; t >= 0; t--) {
        for (int i = 0; i < numStates; i++) {
            bwd[i][t] = 0;
            for (int j = 0; j < numStates; j++)
                bwd[i][t] += (bwd[j][t + 1] * a[i][j] * b[j][o[t + 1]]);
        }
    }
    return bwd;
}

void HMM::print(){
    //TODO
}

vector<double> HMM::getPi(){
    return this->pi;
}
void HMM::setPi(vector<double>& pi){
    this->pi = pi;
}
vector<vector<double>> HMM::getA(){
    return this->a;
}
void HMM::setA(vector<vector<double>>& a){
    this->a = a;
}
vector<vector<double>> HMM::getB(){
    return this->b;
}
void HMM::setB(vector<vector<double>>& b){
    this->b = b;
}