//
//  Projection.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 11/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Projection_hpp
#define Projection_hpp

#include <stdio.h>
#include <glm/glm.hpp>

class Projection
{
public:
    Projection();
    ~Projection();
    
    glm::vec2 project();
};

#endif /* Projection_hpp */
