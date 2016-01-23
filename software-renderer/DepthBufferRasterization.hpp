//
//  DepthBufferRasterization.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 19/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef DepthBufferRasterization_hpp
#define DepthBufferRasterization_hpp

#include <stdio.h>

#include "RasterizationStage.hpp"
#include "DepthBuffer.h"

class DepthBufferRasterization : public RasterizationStage
{
public:
    DepthBufferRasterization();
    ~DepthBufferRasterization();
    
    void init(Screen* screen, Camera* camera ,Mesh* mesh, float delta);
    void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta, Event* event);
protected:
    const float farClippingPLane = 1000;
    DepthBuffer* depthBuffer;
};

#endif /* DepthBufferRasterization_hpp */