//
//  InterpolationRasterization.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 21/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef InterpolationRasterization_hpp
#define InterpolationRasterization_hpp

#include <stdio.h>
#include "DepthBufferRasterization.hpp"

class InterpolationRasterization : public DepthBufferRasterization
{
public:
    InterpolationRasterization();
    ~InterpolationRasterization();
    
    void init(Screen* screen, Camera* camera ,Mesh* mesh, float delta);
    void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta, Event* event);
};

#endif /* InterpolationRasterization_hpp */
