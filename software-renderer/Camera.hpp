//
//  Camera.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <stdio.h>
#include <glm/glm.hpp>

class Camera {

public:
    Camera();
    ~Camera();
    
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::vec3 getTarget();
    void setTarget(glm::vec3 target);
private:
    glm::vec3 position;
    glm::vec3 target;
};

#endif /* Camera_hpp */
