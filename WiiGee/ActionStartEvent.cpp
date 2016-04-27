//
//  ActionStartEvent.cpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "ActionStartEvent.hpp"

/**
 * Is true if this button press has been done by the
 * individual defined RecognitionButton which has to be
 * set during initialization of a Wiimote.
 *
 * @return Is this button press initiated by the recognition button.
 * @see device.Wiimote#setRecognitionButton(int) setRecognitionButton()
 */
bool ActionStartEvent::isRecognitionInitEvent(){
    return this->recognitionbutton;
}

/**
 * Is true if this button press has been done by the
 * individual defined TrainButton which has to be
 * set during initialization of a Wiimote.
 *
 * @return Is this button pres initiated by the training button.
 * @see device.Wiimote#setTrainButton(int) setTrainButton()
 */
bool ActionStartEvent::isTrainInitEvent() {
    return this->trainbutton;
}

/**
 * Is true if this button press has been done by the
 * individual defined CloseGestureButton which has to be
 * set during initialization of a Wiimote.
 *
 * @return Is this button press initiated by the close gesture button.
 * @see device.Wiimote#setCloseGestureButton(int) setCloseGestureButton()
 */
bool ActionStartEvent::isCloseGestureInitEvent() {
    return this->closegesturebutton;
}