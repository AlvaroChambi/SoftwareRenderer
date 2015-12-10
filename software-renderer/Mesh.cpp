//
//  Mesh.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Mesh.hpp"

Mesh::Mesh()
{}

Mesh::Mesh(int numVertices)
{
    vertices = std::vector<glm::vec3>(numVertices);
}

Mesh::~Mesh()
{

}

glm::vec3 Mesh::getPosition()
{
    return position;
}

void Mesh::setPosition(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Mesh::getRotation()
{
    return rotation;
}

void Mesh::setRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
}

std::vector<glm::vec3> Mesh::getVertices()
{
    return vertices;
}

void Mesh::setVertices(std::vector<glm::vec3> vertices)
{
    this->vertices = vertices;
}
