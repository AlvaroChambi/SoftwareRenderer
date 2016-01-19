//
//  RasterizationStage.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 15/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "RasterizationStage.hpp"

RasterizationStage::RasterizationStage()
{

}

RasterizationStage::~RasterizationStage()
{

}

void RasterizationStage::init(Screen *screen, Camera *camera, Mesh *mesh, float delta)
{
    projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 1.0f);
}

void RasterizationStage::render(Screen *screen, Camera *camera, Mesh *mesh, float delta)
{
    for (uint32_t i = 0; i < mesh->getNumTriangles(); ++i) {
        const glm::vec3 v0 = mesh->getVertices()[i * 3];
        const glm::vec3 v1 = mesh->getVertices()[i * 3 + 1];
        const glm::vec3 v2 = mesh->getVertices()[i * 3 + 2];
        // [comment]
        // Convert the vertices of the triangle to raster space
        // [/comment]
        glm::vec3 rasterV0, rasterV1, rasterV2;
        glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(),
                                           camera->getTarget(),
                                           glm::vec3(0.0f, 1.0f, 0.0f)
                                           );
        
        glm::mat4 translationMatrix = glm::translate(mesh->getPosition());
        glm::mat4 rotationMatrix = glm::rotate(delta * 1.0f, glm::vec3(1.0f,1.0f,0.0f));
        glm::mat4 scaleMatrix = glm::scale(glm::vec3(0.25,0.25,0.25));
        glm::mat4 worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * worldMatrix;

    
        rasterV0 = pointToRaster(v0,transformationMatrix);
        rasterV1 = pointToRaster(v1, transformationMatrix);
        rasterV2 = pointToRaster(v2, transformationMatrix);
        
        float xmin = min3(rasterV0.x, rasterV1.x, rasterV2.x);
        float ymin = min3(rasterV0.y, rasterV1.y, rasterV2.y);
        float xmax = max3(rasterV0.x, rasterV1.x, rasterV2.x);
        float ymax = max3(rasterV0.y, rasterV1.y, rasterV2.y);
        
        // the triangle is out of screen
        if (xmin > screen->getWidth() - 1 || xmax < 0 || ymin > screen->getHeight() - 1 || ymax < 0) continue;
        
        // be careful xmin/xmax/ymin/ymax can be negative. Don't cast to uint32_t
        uint32_t x0 = std::max(int32_t(0), (int32_t)(std::floor(xmin)));
        uint32_t x1 = std::min(int32_t(screen->getWidth()) - 1, (int32_t)(std::floor(xmax)));
        uint32_t y0 = std::max(int32_t(0), (int32_t)(std::floor(ymin)));
        uint32_t y1 = std::min(int32_t(screen->getHeight()) - 1, (int32_t)(std::floor(ymax)));
        // [comment]
        // Inner loop
        // [/comment]
        for (uint32_t y = y0; y <= y1; ++y) {
            for (uint32_t x = x0; x <= x1; ++x) {
                glm::vec3 pixelSample(x + 0.5, y + 0.5, 0);
                float w0 = edgeFunction(rasterV1, rasterV2, pixelSample);
                float w1 = edgeFunction(rasterV2, rasterV0, pixelSample);
                float w2 = edgeFunction(rasterV0, rasterV1, pixelSample);
                if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                    screen->drawPoint(glm::vec2(x,y), Color(255,255,255));
                }
            }
        }
    }
}