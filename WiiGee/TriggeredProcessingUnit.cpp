//
//  TriggeredProcessingUnit.cpp
//  WiiGee
//
//  Created by Nextep-3 on 27.04.16.
//  Copyright © 2016 Nextep-3. All rights reserved.
//

#include "TriggeredProcessingUnit.hpp"

TriggeredProcessingUnit::TriggeredProcessingUnit(){
    this->learning = false;
    this->analyzing = false;
}

void TriggeredProcessingUnit::accelerationReceived(std::shared_ptr<AccelerationEvent> event){
    if(this->learning || this->analyzing) {
        this->current->add(event); // add event to gesture
    }
}

void TriggeredProcessingUnit::buttonPressReceived(std::shared_ptr<ButtonPressedEvent> event){
    this->handleStartEvent(event);
}

void TriggeredProcessingUnit::buttonReleaseReceived(std::shared_ptr<ButtonReleasedEvent> event) {
    this->handleStopEvent(event);
}

void TriggeredProcessingUnit::handleStartEvent(shared_ptr<ActionStartEvent> event){
    
    // TrainButton = record a gesture for learning
    if((!this->analyzing && !this->learning) &&
       event->isTrainInitEvent()) {
//        Log.write("Training started!");
        this->learning=true;
    }
    
    // RecognitionButton = record a gesture for recognition
    if((!this->analyzing && !this->learning) &&
       event->isRecognitionInitEvent()) {
//        Log.write("Recognition started!");
        this->analyzing=true;
    }
    
    // CloseGestureButton = starts the training of the model with multiple
    // recognized gestures, contained in trainsequence
    if((!this->analyzing && !this->learning) &&
       event->isCloseGestureInitEvent()) {
        
        if(this->trainsequence.size()>0) {
//            Log.write("Training the model with "+this->trainsequence.size()+" gestures...");
            this->learning=true;
            
            shared_ptr<GestureModel> m(new GestureModel());
            m->train(this->trainsequence);
            m->print();
            this->classifier.addGestureModel(m);
            
            this->trainsequence.clear();
            this->learning=false;
        } else {
//            Log.write("There is nothing to do. Please record some gestures first.");
        }
    }
}

void TriggeredProcessingUnit::handleStopEvent(shared_ptr<ActionStopEvent> event){
    if(this->learning) { // button release and state=learning, stops learning
        if(this->current->getCountOfData() > 0) {
//            Log.write("Finished recording (training)...");
//            Log.write("Data: "+this->current.getCountOfData());
            shared_ptr<Gesture> gesture(new Gesture(this->current));
            this->trainsequence.push_back(gesture);
            this->current.reset(new Gesture());
            this->learning = false;
        } else {
//            Log.write("There is no data.");
//            Log.write("Please train the gesture again.");
            this->learning = false; // ?
        }
    }
    
    else if(this->analyzing) { // button release and state=analyzing, stops analyzing
        if(this->current->getCountOfData()>0) {
//            Log.write("Finished recording (recognition)...");
//            Log.write("Compare gesture with "+this->classifier.getCountOfGestures()+" other gestures.");
            shared_ptr<Gesture> gesture(new Gesture(this->current));
            
            int recognized = this->classifier.classifyGesture(gesture);
            if(recognized!=-1) {
                double recogprob = this->classifier.getLastProbability();
                this->fireGestureEvent(true, recognized, recogprob);
//                Log.write("######");
//                Log.write("Gesture No. "+recognized+" recognized: "+recogprob);
//                Log.write("######");
            } else {
                this->fireGestureEvent(false, 0, 0.0);
//                Log.write("######");
//                Log.write("No gesture recognized.");
//                Log.write("######");
            }
            
            this->current.reset(new Gesture());
            this->analyzing=false;
        } else {
//            Log.write("There is no data.");
//            Log.write("Please recognize the gesture again.");
            this->analyzing=false; // ?
        }
    }
}

void TriggeredProcessingUnit::loadGesture(string filename){
//    GestureModel g = org.wiigee.core.util.FileIO.readFromFile(filename);
//    this.classifier.addGestureModel(g);
}

void TriggeredProcessingUnit::saveGesture(int id, string filename){
//    org.wiigee.core.util.FileIO.writeToFile(this.classifier.getGestureModel(id), filename);
}