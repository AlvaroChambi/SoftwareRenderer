//
//  ScratchPixelTriangleRaster.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 15/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "ScratchPixelTriangleRaster.hpp"


ScratchPixelTriangleRaster::ScratchPixelTriangleRaster()
{

}

ScratchPixelTriangleRaster::~ScratchPixelTriangleRaster()
{

}

float ScratchPixelTriangleRaster::edgeFunction(const Vec2 &a, const Vec2 &b, const Vec2 &c)
{ return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); }

void ScratchPixelTriangleRaster::render(Screen *screen, Camera *camera, Mesh *mesh, float delta)
{
    
    Vec2 v0 = {491.407, 411.407};
    Vec2 v1 = {148.593, 68.5928};
    Vec2 v2 = {148.593, 411.407};
    Vec3 c0 = {1, 0, 0};
    Vec3 c1 = {0, 1, 0};
    Vec3 c2 = {0, 0, 1};
    
    const uint32_t w = 640;
    const uint32_t h = 480;
    
    Rgb *framebuffer = new Rgb[w * h];
    memset(framebuffer, 0x0, w * h * 3);
    
    float area = edgeFunction(v0, v1, v2);
    
    for (uint32_t j = 0; j < h; ++j) {
        for (uint32_t i = 0; i < w; ++i) {
            Vec2 p = {i + 0.5f, j + 0.5f};
            float w0 = edgeFunction(v1, v2, p);
            float w1 = edgeFunction(v2, v0, p);
            float w2 = edgeFunction(v0, v1, p);
            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                w0 /= area;
                w1 /= area;
                w2 /= area;
                float r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
                float g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
                float b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
                unsigned char rChar = (unsigned char)(r * 255);
                unsigned char gChar = (unsigned char)(g * 255);
                unsigned char bChar = (unsigned char)(b * 255);
                framebuffer[j * w + i][0] = rChar;
                framebuffer[j * w + i][1] = gChar;
                framebuffer[j * w + i][2] = bChar;
                Color color = Color();
                color.r = (unsigned char)(r * 255);
                color.g = (unsigned char)(g * 255);
                color.b = (unsigned char)(b * 255);
                screen->drawPoint(glm::vec2(i,j), color);
            }
        }
    } 
    
}