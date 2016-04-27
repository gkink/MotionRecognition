//
//  GestureListener.hpp
//  WiiGee
//
//  Created by Nextep-3 on 20.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef GestureListener_hpp
#define GestureListener_hpp

#include "GestureEvent.hpp"

class GestureListener {
    
    /**
     * This method would be called if a gesture has been recognized.
     *
     * @param event The GestureEvent containing information about
     * the recognized gesture.
     */
public:
   virtual void gestureReceived(GestureEvent event) = 0;
};

#endif /* GestureListener_hpp */
