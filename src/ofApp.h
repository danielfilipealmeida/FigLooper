/*
 FigLooper
 2016 Daniel Almeida
 daniel@danielfilipea.net
 */


#pragma once

#ifndef __ofApp__
#define __ofApp__

#include "ofMain.h"
#include "ofxGui.h"
#include "Audio.hpp"
#include "Loop.hpp"
#include <vector>


typedef enum {
    Key_Space   = 32,
    Key_Enter   = 13,
    Key_Escape  = 27
} Keys;

typedef enum {
    Idle                = -1,
    WaitingForFirstLoop = 0,
    RecordingFirstLoop,
    RecordingMoreLoops,
    PlayingLoops
} AppState;



class ofApp : public ofBaseApp{
private:
    AppState        state;
    int             inputDeviceId;
    int             bufferSize;
    int             samplesPerSecond;
    vector <Loop *> loops;
    unsigned long   loopSize;
    int             loopPlaying;
    ofSoundStream   *inputSoundStream, *outputSoundStream;
    Loop*           currentLoop;
    float*          leftInput;
    float*          rightInput;
    
    
public:
 
    
#pragma mark main methods
    
    void setup();
	void update();
	void draw();
	
    
    
#pragma mark event handling
   
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    

    
#pragma mark loops
    
    void startSavingNewLoop();
    
#pragma mark state management
    
    void changeState();
    void changeState(AppState fromState, AppState toState);
    void changeStateToPlayLoops();
    
    
#pragma mark audio in and out control
    
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut(float * input, int bufferSize, int nChannels);

    
private:
    ofxPanel gui;
    ofxFloatSlider slider;
    
};

#endif
