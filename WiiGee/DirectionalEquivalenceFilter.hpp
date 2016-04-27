//
//  DirectionalEqu	ivalenceFilter.hpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef DirectionalEquivalenceFilter_hpp
#define DirectionalEquivalenceFilter_hpp

#include <stdio.h>
#include "Filter.hpp"

class DirectionalEquivalenceFilter: public Filter {
    
public:
    DirectionalEquivalenceFilter(): Filter() {
        this->reset();
    }

    void reset();
    vector<double>& filterAlgorithm(vector<double>& vec);
    void setSensivity(double sensivity);
    double getSensivity();

    
private:
    double sensivity;
    vector<double> reference{0.0, 0.0, 0.0};
    void setReference(vector<double>& vec);
};


#endif /* DirectionalEquivalenceFilter_hpp */
