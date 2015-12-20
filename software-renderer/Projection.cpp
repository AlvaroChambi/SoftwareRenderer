//
//  Projection.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 11/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Projection.hpp"

Projection::Projection()
{

}

Projection::~Projection()
{

}

glm::vec2 Projection::project()
{
    int width = 640, height = 480; // dimension of the image in pixels
    glm::vec3 P = glm::vec3(-1, 2, 10);
    glm::vec2 P_proj;
    P_proj.x = P.x / P.z; // -0.1
    P_proj.y = P.y / P.z; // 0.2
    // convert from screen space coordinates to normalized coordinates
    glm::vec2 P_proj_nor;
    P_proj_nor.x = (P_proj.x + 1) / 2; // (-0.1 + 1) / 2 = 0.45
    P_proj_nor.y = (1 - P_proj.y ) / 2; // (1 - 0.2) / 2 = 0.4
    // finally, convert to raster space
    glm::vec2 P_proj_raster;
    P_proj_raster.x = (int)(P_proj_nor.x * width);
    P_proj_raster.y = (int)(P_proj_nor.y * height);
    if (P_proj_raster.x == width) P_proj_raster.x = width - 1;
    if (P_proj_raster.y == height) P_proj_raster.y = height - 1;
    return P_proj_raster;
}