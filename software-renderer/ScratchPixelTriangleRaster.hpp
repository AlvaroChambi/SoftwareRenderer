//
//  ScratchPixelTriangleRaster.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 15/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ScratchPixelTriangleRaster_hpp
#define ScratchPixelTriangleRaster_hpp

#include <stdio.h>
#include "Process.h"

class ScratchPixelTriangleRaster : public Process
{
public:
    typedef float Vec2[2];
    typedef float Vec3[3];
    typedef unsigned char Rgb[3];
    
    ScratchPixelTriangleRaster();
    ~ScratchPixelTriangleRaster();
    
    float edgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c);
    void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta);

};

#endif /* ScratchPixelTriangleRaster_hpp */
