//
//  DepthBuffer.h
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 20/01/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __software_renderer__DepthBuffer__
#define __software_renderer__DepthBuffer__

#include <stdio.h>

class DepthBuffer
{
public:
    const int FAR_CLIPPING_PLANE = 10000;
    DepthBuffer(int width, int height);
    ~DepthBuffer();
    
    void putDepthValue(int x, int y, float depthValue);
    bool isVisible(int x, int y, float depthValue);
    void clear();
    int getOverridedPoints();
    int getStoredPoints();
private:
    int storedPoints;
    int overridedPoints;
    float* depthBuffer;
    int width;
    int height;
};

#endif /* defined(__software_renderer__DepthBuffer__) */
