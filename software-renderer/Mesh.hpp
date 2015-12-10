//
//  Mesh.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <glm/glm.hpp>
#include <string>
#include <vector>

class Mesh{
public:
    Mesh();
    Mesh(int numVertices);
    ~Mesh();
    
    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::vec3 getRotation();
    void setRotation(glm::vec3 rotation);
    std::vector<glm::vec3> getVertices();
    void setVertices(std::vector<glm::vec3> vertices);
private:
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
    std::vector<glm::vec3> vertices;
};

#endif /* Mesh_hpp */
