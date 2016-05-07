//
//  GraphicsUtils.cpp
//  FigLooper
//
//  Created by Daniel Almeida on 30/04/16.
//
//

#include "GraphicUtils.hpp"


GraphicRectangle GraphicUtils::makeRect(float x, float y, float w, float h) {
    GraphicRectangle result;
    
    result.origin.x = x;
    result.origin.y = y;
    result.w = w;
    result.h = h;
    
    return result;
}

void GraphicUtils::drawAudioChannel(
                                    float               *channelData,
                                    int                 bufferSize,
                                    string              label,
                                    GraphicRectangle    rect
                                    )
{
    float x2;
    
    x2 = rect.h / bufferSize * 2;
    
    ofSetColor(225);
    ofNoFill();
    
    // draw the left channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(rect.origin.x, rect.origin.y, 0);
    
    ofSetColor(225);
    ofDrawBitmapString(label, 4, 18);
    
    ofSetLineWidth(1);
    ofDrawRectangle(0, 0, rect.w, rect.h);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < bufferSize; i++){
        ofVertex(i*x2, rect.h / 2 -channelData[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();

    
}


void GraphicUtils::drawAudioChannels(
                                     float              *left,
                                     float              *right,
                                     int                bufferSize,
                                     GraphicRectangle   rect
                                     )
{
    GraphicRectangle leftRect, rightRect;
    
    leftRect = GraphicUtils::makeRect(rect.origin.x, rect.origin.y, rect.w, rect.h/2);
    rightRect = GraphicUtils::makeRect(rect.origin.x, rect.origin.y+ leftRect.h, rect.w, leftRect.h);
    
    
    GraphicUtils::drawAudioChannel(left, bufferSize, "Left", leftRect);
    GraphicUtils::drawAudioChannel(right, bufferSize, "Right", rightRect);
    /*
    std::map<string,float> defaultRect = {
        {"x",       0},
        {"y",       0},
        {"width",   200},
        {"height",  200}
    };
    rect.insert(defaultRect.begin(), defaultRect.end());
    */
    
    /*
    ofSetColor(225);
    ofNoFill();
    
    // draw the left channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 170, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Left Channel", 4, 18);
    
    ofSetLineWidth(1);
    ofDrawRectangle(0, 0, 512, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < bufferSize; i++){
        ofVertex(i*2, 100 -left[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
    
    
    // draw the right channel:
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(32, 370, 0);
    
    ofSetColor(225);
    ofDrawBitmapString("Right Channel", 4, 18);
    
    ofSetLineWidth(1);
    ofDrawRectangle(0, 0, 512, 200);
    
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    
    ofBeginShape();
    for (unsigned int i = 0; i < bufferSize; i++){
        ofVertex(i*2, 100 -right[i]*180.0f);
    }
    ofEndShape(false);
    
    ofPopMatrix();
    ofPopStyle();
     */
    
}