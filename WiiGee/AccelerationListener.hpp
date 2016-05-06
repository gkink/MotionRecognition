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
#include "MotionStopEvent.hpp"
#include "MotionStartEvent.hpp"
#include <memory>

class AccelerationListener {
    
public:
    /**
     * This method would be called if a Device source has been accelerated.
     *
     * @param event The acceleration representation as an event.
     */
    virtual void accelerationReceived(std::shared_ptr<AccelerationEvent> event) = 0;
    
    /**
     * This method would be called if a Device is in idle state and then a
     * motion starts or if a Device is in motion and then the motion stops and
     * the Device is in idle state.
     *
     * @param event This is the event which contains if the Wiimote is now
     * in motion or not.
     */

    virtual void motionStartReceived(std::shared_ptr<MotionStartEvent> event) = 0;
    
    /**
     * This method would be called if a Device is in motion and then the motion
     * stops and the Device is in idle state.
     *
     * @param event This is the event which contains if the Device is now
     * in motion or not.
     */
    virtual void motionStopReceived(std::shared_ptr<MotionStopEvent> event) = 0;
    
};
#endif /* AccelerationListener_hpp */
