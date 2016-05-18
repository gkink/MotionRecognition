//
//  Cocos2dxDevice.hpp
//  WiiGee
//
//  Created by Nextep-3 on 10.05.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef Cocos2dxDevice_hpp
#define Cocos2dxDevice_hpp

#include "GeneralDevice.hpp"

class Cocos2dxDevice: public GeneralDevice{
public:
    void onSensorChanged(double x, double y, double z);
};

#endif /* Cocos2dxDevice_hpp */
