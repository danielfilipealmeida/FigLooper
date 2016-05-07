//
//  Audio.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 23/04/16.
//
//

#ifndef Audio_hpp
#define Audio_hpp

#include <stdio.h>
#include "ofMain.h"

typedef enum  {
    AudioInput = 0,
    AudioOutput
} AudioChannelType;

class AudioChannel : public ofBaseApp{
public:

    AudioChannel(AudioChannelType _type, int _deviceId);
    
    static AudioChannel* newInputChannel(int _deviceId = 0);
    static AudioChannel* newOutputChannel(int _deviceId = 0);
  
private:
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int deviceId;
    int bufferSize;
    int samplesPerSecond;
    
    AudioChannelType    type;
    ofSoundStream       soundStream;
    
    void audioIn(
                 float  *input,
                 int    bufferSize,
                 int    nChannels
                 );
    
    void audioOut(float * input, int bufferSize, int nChannels);
    
};

class Audio {
public:
    static Audio*   getAudioDevice(
                                   int inputDeviceId    = 0,
                                   int outputDeviceId   = 0
                                   );
    
    
    static void splitStreamIntoChannels(
                                        float   *input,
                                        int     bufferSize,
                                        float   *left,
                                        float   *right
                                        );
    
    
protected:
    Audio();
    
private:
    void constructor(int inputDeviceId,
                     int outputDeviceId
                     );
    
    void updateInput();
    void updateOutput();
 
    static Audio*   _instance;
    
    AudioChannel    *input;
    AudioChannel    *output;
};
#endif /* Audio_hpp */
