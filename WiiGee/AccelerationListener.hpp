//
//  AccelerationListener.hpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef AccelerationListener_hpp
#define AccelerationListener_hpp

#include "AccelerationEvent.hpp"
#include <memory>

class AccelerationListener {
    
public:
    /**
     * This method would be called if a Device source has been accelerated.
     *
     * @param event The acceleration representation as an event.
     */
    virtual void accelerationReceived(std::shared_ptr<AccelerationEvent> event) = 0;
};
#endif /* AccelerationListener_hpp */
