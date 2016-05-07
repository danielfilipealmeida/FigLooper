//
//  GraphicsUtils.hpp
//  FigLooper
//
//  Created by Daniel Almeida on 30/04/16.
//
//

#ifndef GraphicsUtils_hpp
#define GraphicsUtils_hpp

#include "ofMain.h"
#include <stdio.h>
#include <map>


typedef struct GraphicRectangle {
    ofPoint origin;
    float   w;
    float   h;
} GraphicRectangle;

class GraphicUtils {
    
public:
    static GraphicRectangle makeRect(float x, float y, float w, float h);
    
    static void drawAudioChannel(
                                 float   *channelData,
                                 int     bufferSize,
                                 string  label,
                                 GraphicRectangle    rect
    );
    
    static void drawAudioChannels(
                                  float                     *left,
                                  float                     *right,
                                  int                       bufferSize,
                                  GraphicRectangle   rect
                                  );
};

#endif /* GraphicsUtils_hpp */
