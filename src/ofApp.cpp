#include "ofApp.h"
#include "GraphicUtils.hpp"
#include <map>

/*
std::vector<string> stateStrings = {
    "Idle",
    "Waiting for first loop",
    "Recording first loop",
    "Recording more loops",
    "Playing Loop"
};
 */
std::map<int, string> stateStrings = {
    {   -1,     "Idle"},
    {   0,      "Waiting for first loop"},
    {   1,      "Recording first loop"},
    {   2,      "Recording more loops"},
    {   3,      "Playing Loops"},
    
};


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    
    gui.setup();
    gui.add(slider.setup("slider", 0, 1.0, 0.5));
    
    state               = WaitingForFirstLoop;
    bufferSize          = 256;
    samplesPerSecond    = 44100;
    loopSize            = 0;
    currentLoop         = NULL;
    leftInput           = new float[256];
    rightInput          = new float[256];
    
    
    
    // init input
    inputDeviceId       = 0;
    
    inputSoundStream = new ofSoundStream();
    inputSoundStream->printDeviceList();
    inputSoundStream->setDeviceID(inputDeviceId);
    inputSoundStream->setup(this, 0, 2, samplesPerSecond, bufferSize, 2);
    
    
    // init output
    inputDeviceId  = 2;
    outputSoundStream = new ofSoundStream();
    outputSoundStream->setDeviceID(inputDeviceId);
    outputSoundStream->setup(this, 2, 0, samplesPerSecond, bufferSize, 2);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    GraphicUtils::drawAudioChannels(leftInput,
                                    rightInput,
                                    bufferSize,
                                    GraphicUtils::makeRect(0,0,200,200)
                                    );
    
    gui.draw();
    ofDrawBitmapString(stateStrings[(unsigned int)state],0,600);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "key: " << ofToString(key) << endl;
    
    
    switch (key) {
        case Key_Space:
            changeState();
            break;
            
        case Key_Enter:
            changeStateToPlayLoops();
            break;
            
        case Key_Escape:
            
            break;
            
        default:
            
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

#pragma mark loops

void ofApp::startSavingNewLoop() {
    currentLoop = new Loop();
    loops.push_back(currentLoop);
    currentLoop->startSaving();
}

#pragma mark state management



void ofApp::changeState() {
    cout << state << endl;
    if (state >=0 && state <2) {
        changeState(state, (AppState)( (int)state +1));
    }
    if (state == 2) {
        startSavingNewLoop();
    }
}



void ofApp::changeState(AppState fromState, AppState toState) {
    cout << fromState << "-" << toState << endl;
    if (toState > 0) {
        if (toState - fromState != 1) return;
        
        switch (toState) {
            case RecordingFirstLoop:
                startSavingNewLoop();
                break;
                
            case RecordingMoreLoops:
                // save the previous loop
                currentLoop->stopSaving();
                
                startSavingNewLoop();
                break;
                
            case PlayingLoops:
                changeStateToPlayLoops();
                break;
                
            default:
                
                break;
                
        }
        
        state = toState;
        return;
    }
}







#pragma mark audio in and out control




void ofApp::changeStateToPlayLoops() {
    if (state == RecordingFirstLoop || state == RecordingMoreLoops) {
        currentLoop->stopSaving();
        currentLoop = NULL;
    }
    
    state = PlayingLoops;
    
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
    Audio::splitStreamIntoChannels(input, bufferSize, leftInput, rightInput);
    
    
    if (currentLoop == NULL) return;
    if (state < RecordingFirstLoop && state >RecordingMoreLoops) return;
    
    try {
        currentLoop->saveData(input, bufferSize, nChannels);
        //currentLoop->draw();
    }
    catch (exception e) {
        cout << e.what() << endl;
    }
    
    
    
}

void ofApp::audioOut(float * input, int bufferSize, int nChannels) {
    for (
         vector <Loop *>::iterator it = loops.begin();
         it != loops.end();
         it++
    ) {
        Loop *loop = *it;
        
        if (loop != currentLoop) loop->playCurrentChunk(input, bufferSize, nChannels);
    }
}

