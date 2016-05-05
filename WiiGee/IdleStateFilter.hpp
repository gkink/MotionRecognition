//
//  IdleStateFilter.hpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef IdleStateFilter_hpp
#define IdleStateFilter_hpp

#include <stdio.h>
#include "Filter.hpp"

class IdleStateFilter: public Filter{
    
public:
    IdleStateFilter():Filter(), sensivity{0.1} {}
    void reset();
    vector<double>& filterAlgorithm(vector<double>& vec);
    void setSensivity(double sensivity);
    double getSensivity();
    
private:
    double sensivity;
    
 
};

#endif /* IdleStateFilter_hpp */
