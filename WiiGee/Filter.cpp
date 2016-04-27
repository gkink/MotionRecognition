//
//  Filter.cpp
//  WiiGee
//
//  Created by Nextep-3 on 18.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "Filter.hpp"

vector<double>& Filter::filter(vector<double>& vec){
    
    if(vec.empty()) {
        return vec;
    } else {
        return filterAlgorithm(vec);
    }
}
