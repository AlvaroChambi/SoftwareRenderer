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


glm::mat4 buildProjectionMatrix(const float &angleOfView, const float &near, const float &far)
{
    glm::mat4 M = glm::mat4(1);
    // do some work here
    float scale = 1 / tan(angleOfView * 0.5 * M_PI / 180);
    M[0][0] = scale;
    M[1][1] = scale;
    M[2][2] = -far / (far - near);
    M[3][2] = -far * near / (far - near);
    M[2][3] = -1;
    M[3][3] = 0;
    
    return M;
}

glm::vec3 multPointMatrix(glm::vec3 in, glm::mat4 M)
{
    glm::vec3 out = glm::vec3();
    //out = in * Mproj;
    out.x   = in.x * M[0][0] + in.y * M[1][0] + in.z * M[2][0] + /* in.z = 1 */ M[3][0];
    out.y   = in.x * M[0][1] + in.y * M[1][1] + in.z * M[2][1] + /* in.z = 1 */ M[3][1];
    out.z   = in.x * M[0][2] + in.y * M[1][2] + in.z * M[2][2] + /* in.z = 1 */ M[3][2];
    float w = in.x * M[0][3] + in.y * M[1][3] + in.z * M[2][3] + /* in.z = 1 */ M[3][3];
    
    // normalize if w is different than 1 (convert from homogeneous to Cartesian coordinates)
    if (w != 1) {
        out.x /= w;
        out.y /= w;
        out.z /= w;
    }
    return out;
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

void Projection::testProject()
{
    /*
    float nearClippingPlane = 0.1;
    glm::vec3 camera = glm::vec3(0,0,10);
    
    glm::mat4 worldMatrix = glm::mat4(1);
    glm::vec2 screen;
    screen.x = nearClippingPlane * camera.x / -camera.z;
    screen.y = nearClippingPlane * camera.y / -camera.z;
    glm::vec2 pNDC;
    pNDC.x = 2 * screen.x / (r - l) - (r + l) / (r - l);
    pNDC.y = 2 * screen.y / (t - b) - (t + b) / (t - b);
    
    glm::vec3 pRaster;
    pRaster.x = (pScreen.x + 1) / 2 * imageWidth;
    // in raster space y is down so invert direction
    pRaster.y = (1 - pScreen.y) / 2 * imageHeight;
    // store the point camera space z-coordinate (as a positive value)
    pRaster.z = -pCamera.z;*/
}
