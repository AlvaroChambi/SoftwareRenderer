//
//  ProjectionStage.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 14/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ProjectionStage.hpp"

ProjectionStage::ProjectionStage()
{

}

ProjectionStage::~ProjectionStage()
{

}

void ProjectionStage::render(Screen *screen, Camera *camera, Mesh *mesh, float delta)
{
    glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(),
                                       camera->getTarget(),
                                       glm::vec3(0.0f, 1.0f, 0.0f)
                                       );
    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 1.0f);
    
    glm::mat4 translationMatrix = glm::translate(mesh->getPosition());
    glm::mat4 rotationMatrix = glm::rotate(delta * 1.0f, glm::vec3(1.0f,1.0f,0.0f));
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(0.25,0.25,0.25));
    glm::mat4 worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * worldMatrix;
    for (glm::vec3 vector : mesh->getVertices()) {
        glm::vec2 point = pointToRaster(vector, transformationMatrix);
        screen->drawPoint(point, Color(255,255,255));
    }
}

glm::vec2 ProjectionStage::pointToRaster(glm::vec3 coord, glm::mat4 transformationMatrix)
{
    glm::vec4 newCoord = glm::vec4(coord, 1.0f);
    glm::vec4 point = transformationMatrix * newCoord;
    int x = std::min(639, (int)((1 - point.x ) * 640*0.5) ) ;
    int y = std::min(479,(int)((1 + point.y) * 480*0.5f));
    
    return glm::vec2(x,y);
}