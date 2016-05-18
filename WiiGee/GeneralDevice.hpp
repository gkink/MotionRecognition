//
//  GeneralDevice.hpp
//  WiiGee
//
//  Created by Nextep-3 on 19.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#ifndef GeneralDevice_hpp
#define GeneralDevice_hpp

class ButtonListener;

#include <vector>
#include <memory>
#include "Filter.hpp"
#include "AccelerationListener.hpp"
#include "ProcessingUnit.hpp"
#include "TriggeredProcessingUnit.hpp"
#include "ProcessingUnit.hpp"
#include <string>

using namespace std;

class GeneralDevice {
    
public:
    static const int MOTION = 0;
    
    GeneralDevice(bool autofiltering);
    void addAccelerationFilter(unique_ptr<Filter> filter);
    void addAccelerationListener(shared_ptr<AccelerationListener> listener);
    void resetAccelerationFilters();
    void addButtonListener(shared_ptr<ButtonListener> listener);
    void addGestureListener(GestureListener* listener);
    
    void fireAccelerationEvent(vector<double>& vec);
    void fireButtonPressedEvent(int button);
    void fireButtonReleasedEvent(int button);
    
    int getRecognitionButton() { return this->recognitionbutton; }
    void setRecognitionButton(int b) { this->recognitionbutton = b; }
    int getTrainButton() { return this->trainbutton; }
    void setTrainButton(int b) { this->trainbutton = b; }
    int getCloseGestureButton() {return this->closegesturebutton; }
    void setCloseGestureButton(int b) { this->closegesturebutton = b; }
    void setAccelerationEnabled(bool enabled) { this->accelerationEnabled = enabled; }
    void loadGesture(string filename) { this->processingunit->loadGesture(filename); }
    void saveGesture(int id, string filename) {this->processingunit->saveGesture(id, filename); }
    
protected:
    int recognitionbutton;
    int trainbutton;
    int closegesturebutton;
    
    bool accelerationEnabled;
   
    vector<unique_ptr<Filter>> accfilters;
    vector<shared_ptr<AccelerationListener>> accelerationlistener;
    vector<shared_ptr<ButtonListener>> buttonlistener;
    
    shared_ptr<ProcessingUnit> processingunit{new TriggeredProcessingUnit()};
};

#endif /* "GeneralDevice_hpp */
