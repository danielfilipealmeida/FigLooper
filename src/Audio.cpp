//
//  Audio.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 23/04/16.
//
//

#include "Audio.hpp"


AudioChannel::AudioChannel(AudioChannelType _type, int _deviceId)
{
    type                = _type;
    deviceId            = _deviceId;
    bufferSize          = 256;
    samplesPerSecond    = 44100;
    
    soundStream.setDeviceID(deviceId);

    switch (type) {
        case AudioInput:
            soundStream.setup(this, 0, 2, samplesPerSecond, bufferSize, 4);
            break;
            
        case AudioOutput:
            soundStream.setup(this, 2, 0, samplesPerSecond, bufferSize, 4);
            break;
    }
    
}


AudioChannel* AudioChannel::newInputChannel(int _deviceId)
{
    AudioChannel *newAudioChannel;
    
    newAudioChannel = new AudioChannel(AudioInput, _deviceId);
    return newAudioChannel;
}

AudioChannel* AudioChannel::newOutputChannel(int _deviceId) {
    AudioChannel *newAudioChannel;
    
    newAudioChannel = new AudioChannel(AudioOutput, _deviceId);
    return newAudioChannel;

}

void AudioChannel::audioIn(
                           float    *input,
                           int      bufferSize,
                           int  nChannels
                           )
{
    cout << "audioIn" <<endl;
}

void AudioChannel::audioOut(
                            float * input,
                            int bufferSize,
                            int nChannels
                            )
{
    cout << "audioOut" <<endl;
}


//////////////////


Audio* Audio::_instance = 0;

Audio::Audio() {}

Audio* Audio::getAudioDevice(
                             int inputDeviceId,
                             int outputDeviceId
                             )
{
    if (_instance == NULL) {
        _instance = new Audio;
        _instance->constructor(inputDeviceId, outputDeviceId);
    }
    return _instance;
}



void Audio::constructor(int inputDeviceId,
                        int outputDeviceId)
{
    cout << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ <<endl;
    
    input   = AudioChannel::newInputChannel(inputDeviceId);
    output  = AudioChannel::newOutputChannel(outputDeviceId);

}

void Audio::updateInput() {
    
}

void Audio::updateOutput() {
    
}



void Audio::splitStreamIntoChannels(
                                    float   *input,
                                    int     bufferSize,
                                    float   *left,
                                    float   *right
                                    )
{
    for (int i = 0; i < bufferSize; i++){
        left[i]     = input[i*2];
        right[i]    = input[i*2+1];
    }

}

