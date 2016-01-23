//
//  ProjectionStage.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 14/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectionStage_hpp
#define ProjectionStage_hpp

#include <stdio.h>
#include "Process.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ProjectionStage : public Process
{
public:
    ProjectionStage();
    ~ProjectionStage();
    
    void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta, Event* event);
private:
    glm::vec2 pointToRaster(glm::vec3 coord, glm::mat4 transformationMatrix);
};

#endif /* ProjectionStage_hpp */
