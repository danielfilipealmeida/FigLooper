//
//  Loop.hpp
//  emptyExample
//
//  Created by Daniel Almeida on 24/04/16.
//
//

#ifndef Loop_hpp
#define Loop_hpp


#include <stdio.h>
#include <fstream>
#include "ofMain.h"
#include "sndfile.h"

#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"


using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::DigestOutputStream;
using Poco::StreamCopier;


typedef enum {
    Stopped = 0,
    OpenForWrite,
    OpenForRead
} LoopState;

class Loop {
private:
    string          path;
    LoopState       state;
    int             saveBufferCounter;
    int             playBufferCounter;
    int             bufferSize;
    SNDFILE         *outfile, *inputfile;
    SF_INFO         info;
    std::ofstream   *out;
    float           *left, *right;
public:
    Loop();
    void startSaving();
    void stopSaving();
    void load();
    void play();
    
    
    void setChannelData(float *data, int bufferSize);
    
    
    void saveData(float * input, int bufferSize, int nChannels);
    void playCurrentChunk(float * input, int bufferSize, int nChannels);
    
    
    void draw();
};


#endif /* Loop_hpp */
