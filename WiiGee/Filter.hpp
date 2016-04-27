//
//  Filter.hpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef Filter_hpp
#define Filter_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class Filter {
    
public:
    virtual ~Filter() {};
    
    virtual vector<double>& filter(vector<double>& vec);
    
    virtual vector<double>& filterAlgorithm(vector<double>& vec) = 0;
    
    virtual void reset() = 0;
};

#endif /* Filter_hpp */
