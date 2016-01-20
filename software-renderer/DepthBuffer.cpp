//
//  DepthBuffer.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 20/01/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(int width, int height) : width(width), height(height), overridedPoints(0), storedPoints(0)
{
    depthBuffer = new float[width * height];
}

DepthBuffer::~DepthBuffer()
{

}

void DepthBuffer::clear()
{
    for(int i = 0; i < width * height; i++){
        depthBuffer[i] = FAR_CLIPPING_PLANE;
    }
    overridedPoints = 0;
    storedPoints = 0;
}

void DepthBuffer::putDepthValue(int x, int y, float depthValue)
{
    if(depthBuffer[y * width + x] != FAR_CLIPPING_PLANE){
        overridedPoints++;
    }
    
    depthBuffer[y * width + x] = depthValue;
    storedPoints++;
}

bool DepthBuffer::isVisible(int x, int y, float depthValue)
{
    float storedDepth = depthBuffer[y * width + x];
    if(storedDepth != FAR_CLIPPING_PLANE){
    }
    return (depthValue < depthBuffer[y * width + x]);
}

int DepthBuffer::getOverridedPoints()
{
    return overridedPoints;
}

int DepthBuffer::getStoredPoints()
{
    return storedPoints;
}
