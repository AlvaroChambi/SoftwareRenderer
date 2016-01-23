//
//  InterpolationRasterization.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 21/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "InterpolationRasterization.hpp"

InterpolationRasterization::InterpolationRasterization()
{

}

InterpolationRasterization::~InterpolationRasterization()
{

}

void InterpolationRasterization::init(Screen *screen, Camera *camera, Mesh *mesh, float delta)
{
    DepthBufferRasterization::init(screen, camera, mesh, delta);
}

void InterpolationRasterization::render(Screen *screen, Camera *camera, Mesh *mesh, float delta)
{
    depthBuffer->clear();
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
        glm::mat4 rotationMatrix = glm::rotate( delta * 0.5f, glm::vec3(1.0f,1.0f,0.0f));
        glm::mat4 scaleMatrix = glm::scale(glm::vec3(0.25,0.25,0.25));
        glm::mat4 worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * worldMatrix;
        
        
        rasterV0 = pointToRaster(v0,transformationMatrix);
        rasterV1 = pointToRaster(v1, transformationMatrix);
        rasterV2 = pointToRaster(v2, transformationMatrix);
        
        // [comment]
        // Precompute reciprocal of vertex z-coordinate
        // [/comment]
        rasterV0.z = 1 / rasterV0.z,
        rasterV1.z = 1 / rasterV1.z,
        rasterV2.z = 1 / rasterV2.z;
        
        float xmin = min3(rasterV0.x, rasterV1.x, rasterV2.x);
        float ymin = min3(rasterV0.y, rasterV1.y, rasterV2.y);
        float xmax = max3(rasterV0.x, rasterV1.x, rasterV2.x);
        float ymax = max3(rasterV0.y, rasterV1.y, rasterV2.y);
        
        // [comment]
        // Prepare vertex attributes. Divde them by their vertex z-coordinate
        // (though we use a multiplication here because v.z = 1 / v.z)
        // [/comment]
        glm::vec2 st0 = mesh->getUvs()[i * 3];
        glm::vec2 st1 = mesh->getUvs()[i * 3 + 1];
        glm::vec2 st2 = mesh->getUvs()[i * 3 + 2];
        
        st0 *= rasterV0.z, st1 *= rasterV1.z, st2 *= rasterV2.z;
        
        // the triangle is out of screen
        if (xmin > screen->getWidth() - 1 || xmax < 0 || ymin > screen->getHeight() - 1 || ymax < 0) continue;
        
        // be careful xmin/xmax/ymin/ymax can be negative. Don't cast to uint32_t
        uint32_t x0 = std::max(int32_t(0), (int32_t)(std::floor(xmin)));
        uint32_t x1 = std::min(int32_t(screen->getWidth()) - 1, (int32_t)(std::floor(xmax)));
        uint32_t y0 = std::max(int32_t(0), (int32_t)(std::floor(ymin)));
        uint32_t y1 = std::min(int32_t(screen->getHeight()) - 1, (int32_t)(std::floor(ymax)));
        float area = edgeFunction(rasterV0, rasterV1, rasterV2);
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
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;
                    float oneOverZ = rasterV0.z * w0 + rasterV1.z * w1 + rasterV2.z * w2;
                    float z = 1 / oneOverZ;
                    if (depthBuffer->isVisible(x, y, z)) {
                        glm::vec2 st = st0 * w0 + st1 * w1 + st2 * w2;
                        st *= z;
                        const int M = 10;
                        float checker = (fmod(st.x * M, 1.0) > 0.5) ^ (fmod(st.y * M, 1.0) < 0.5);
                
                        int r = checker * 255;
                        int g = checker * 255;
                        int b = checker * 255;
                        
                        depthBuffer->putDepthValue(x, y, z);
                        screen->drawPoint(glm::vec2(x,y), Color(r,g,b));
                    }
                }
            }
        }
    }

}