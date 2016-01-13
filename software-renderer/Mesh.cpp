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

Mesh::Mesh(std::string filePath)
{
    vertexIndices = 0;
    uvIndices = 0;
    normalIndices = 0;
}

Mesh::~Mesh()
{

}

void Mesh::loadObj(std::string filePath)
{
    std::string line;
    std::ifstream file(filePath);
    while (std::getline(file, line)) {
        std::istringstream in(line);      //make a stream for the line itself
        std::string type;
        in >> type;                  //and read the first whitespace-separated token
        float x, y, z;
        char separator = '/';
        float vertexIndice, uvIndice, normalIndice;
        std::vector<std::string> indices = std::vector<std::string>(3);
        if(type == "v"){
            in >> x >> y >> z;
            vertices.push_back(glm::vec3(x,y,z));
        }else if(type == "vt"){
            in >> x >> y;
            uvs.push_back(glm::vec2(x,y));
        }else if(type == "vn"){
            in >> x >> y >> z;
            normals.push_back(glm::vec3(x,y,z));
        }else if(type == "f"){
        
            for (int i = 0; i < 3; i++) {
                in >> indices[i];
                char * pch;
                pch = strtok (&indices[i][0],"/");
                while (pch != NULL)
                {
                    printf ("%s",pch);
                    pch = strtok (NULL, "/");
                    float value = *pch;
                    
                }
                printf("\n");
            }
            //std::istringstream stream0(indices[0]);
            //stream0 >> vertexIndice >> separator >> uvIndice >> separator >> normalIndice;
        }
    }
    file.close();
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
