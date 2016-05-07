//
//  Loop.cpp
//  emptyExample
//
//  Created by Daniel Almeida on 24/04/16.
//
//

#include "Loop.hpp"
#include "GraphicUtils.hpp"
#include "Audio.hpp"

Loop::Loop() {
    MD5Engine md5;
    
    md5.update(ofToString(ofGetElapsedTimeMillis()));

    state   = Stopped;
    left    = new float[256];
    right   = new float[256];
    path    = ofFilePath::join("/tmp", DigestEngine::digestToHex(md5.digest()) + ".wav");
    outfile = NULL;
    
    cout << "loop file: " << path << endl;
}


void Loop::setChannelData(float *data, int bufferSize) {
    /*
    for (int i = 0; i < bufferSize; i++){
        left[i]     = data[i*2];
        right[i]    = data[i*2+1];
    }
     */
    Audio::splitStreamIntoChannels(data, bufferSize, left, right);
}

#pragma mark Saving

void Loop::startSaving() {
    int sampleRate;
    
    sampleRate          = 44100;
    saveBufferCounter   = 0;
    info.format         = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.frames         = sampleRate * 30;
    info.samplerate     = sampleRate;
    info.channels       = 2;
    outfile = sf_open (path.c_str(), SFM_WRITE, &info) ;
    if (!outfile)
    {
        cerr<<"Error opening ["<<path.c_str()<<"] : "<<sf_strerror (outfile)<<endl;
        return;
    }
    state = OpenForWrite;
}



void Loop::stopSaving() {
    sf_close(outfile);
    outfile = NULL;
}

void Loop::saveData(float * input, int bufferSize, int nChannels) {
    setChannelData(input, bufferSize);
    saveBufferCounter++;
    sf_write_float(outfile, input, bufferSize*2);
    
    this->bufferSize = bufferSize;
}




#pragma mark Load and Play

void Loop::load() {
    inputfile = sf_open (path.c_str(), SFM_WRITE, &info) ;
}

void Loop::play() {
    state = OpenForRead;
}

void Loop::playCurrentChunk(float * input, int bufferSize, int nChannels) {
    
    if (state!=OpenForRead) return;
    
    float *fileChunk;
    
    sf_seek(inputfile, bufferSize * playBufferCounter, SEEK_SET);
    sf_readf_float(inputfile, fileChunk, bufferSize);
    setChannelData(input, bufferSize);
    for (int i = 0; i < bufferSize; i++){
        input[i] = input[i] + fileChunk[i];
    }
    playBufferCounter++;
    if (playBufferCounter>=saveBufferCounter){
        playBufferCounter = 0;
    }
    
    this->bufferSize = bufferSize;
}



void Loop::draw() {
    //GraphicUtils::drawAudioChannels(left, right, bufferSize, {});
}

