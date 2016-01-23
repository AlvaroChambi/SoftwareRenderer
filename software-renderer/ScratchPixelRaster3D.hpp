//
//  ScratchPixelRaster3D.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 16/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ScratchPixelRaster3D_hpp
#define ScratchPixelRaster3D_hpp

#include <stdio.h>
#include "Process.h"
#include "geometry.h"
#include <fstream>
#include <chrono>

class ScratchPixelRaster3D : public Process
{
public:
    ScratchPixelRaster3D();
    ~ScratchPixelRaster3D();
    
    void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta, Event* event);
    void init(Screen* screen, Camera* camera ,Mesh* mesh, float delta);
    
private:
    const float inchToMm = 25.4;
    enum FitResolutionGate { kFill = 0, kOverscan };
    
    float t, b, l, r;
    Vec3<unsigned char> *frameBuffer;
    float *depthBuffer;
    const uint32_t imageWidth = 640;
    const uint32_t imageHeight = 480;
    const Matrix44f worldToCamera = {0.707107, -0.331295, 0.624695, 0, 0, 0.883452, 0.468521, 0, -0.707107, -0.331295, 0.624695, 0, -1.63871, -5.747777, -40.400412, 1};
    
    const uint32_t ntris = 3156;
    const float nearClippingPLane = 1;
    const float farClippingPLane = 1000;
    float focalLength = 20; // in mm
    // 35mm Full Aperture in inches
    float filmApertureWidth = 0.980;
    float filmApertureHeight = 0.735;
    
    void computeScreenCoordinates(
                                  const float &filmApertureWidth,
                                  const float &filmApertureHeight,
                                  const uint32_t &imageWidth,
                                  const uint32_t &imageHeight,
                                  const FitResolutionGate &fitFilm,
                                  const float &nearClippingPLane, 
                                  const float &focalLength, 
                                  float &top, float &bottom, float &left, float &right 
                                  )
    {
        float filmAspectRatio = filmApertureWidth / filmApertureHeight;
        float deviceAspectRatio = imageWidth / (float)imageHeight;
        
        top = ((filmApertureHeight * inchToMm / 2) / focalLength) * nearClippingPLane;
        right = ((filmApertureWidth * inchToMm / 2) / focalLength) * nearClippingPLane;
        
        // field of view (horizontal)
        float fov = 2 * 180 / M_PI * atan((filmApertureWidth * inchToMm / 2) / focalLength);
        
        float xscale = 1;
        float yscale = 1;
        
        switch (fitFilm) {
            default:
            case kFill:
                if (filmAspectRatio > deviceAspectRatio) {
                    xscale = deviceAspectRatio / filmAspectRatio;
                }
                else {
                    yscale = filmAspectRatio / deviceAspectRatio;
                }
                break;
            case kOverscan:
                if (filmAspectRatio > deviceAspectRatio) {
                    yscale = filmAspectRatio / deviceAspectRatio;
                }
                else {
                    xscale = deviceAspectRatio / filmAspectRatio;
                }
                break;
        }
        
        right *= xscale;
        top *= yscale;
        
        bottom = -top;
        left = -right;
    }
    void convertToRaster(
                         const Vec3f &vertexWorld,
                         const Matrix44f &worldToCamera,
                         const float &l,
                         const float &r,
                         const float &t,
                         const float &b,
                         const float &near, 
                         const uint32_t &imageWidth, 
                         const uint32_t &imageHeight, 
                         Vec3f &vertexRaster 
                         )
    {
        Vec3f vertexCamera;
        
        worldToCamera.multVecMatrix(vertexWorld, vertexCamera);
        
        // convert to screen space
        Vec2f vertexScreen;
        vertexScreen.x = near * vertexCamera.x / -vertexCamera.z;
        vertexScreen.y = near * vertexCamera.y / -vertexCamera.z;
        
        // now convert point from screen space to NDC space (in range [-1,1])
        Vec2f vertexNDC;
        vertexNDC.x = 2 * vertexScreen.x / (r - l) - (r + l) / (r - l);
        vertexNDC.y = 2 * vertexScreen.y / (t - b) - (t + b) / (t - b);
        
        // convert to raster space
        vertexRaster.x = (vertexNDC.x + 1) / 2 * imageWidth;
        // in raster space y is down so invert direction
        vertexRaster.y = (1 - vertexNDC.y) / 2 * imageHeight;
        vertexRaster.z = -vertexCamera.z;
    }
    
    float min3(const float &a, const float &b, const float &c)
    { return std::min(a, std::min(b, c)); }
    
    float max3(const float &a, const float &b, const float &c)
    { return std::max(a, std::max(b, c)); }
    
    float edgeFunction(const Vec3f &a, const Vec3f &b, const Vec3f &c)
    { return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); }
    
    
};

#endif /* ScratchPixelRaster3D_hpp */
