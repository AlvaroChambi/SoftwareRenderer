//
//  RasterizationImplementation.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 30/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef RasterizationImplementation_hpp
#define RasterizationImplementation_hpp

#include <stdio.h>
#include "geometry.h"
#include <fstream>
#include <chrono>
#include <iostream>
#include "cow.h"
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
#include <list>

static const float inchToMm = 25.4;
class RasterizationImplementation
{
public:
    
    enum FitResolutionGate { kFill = 0, kOverscan };
    
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
    RasterizationImplementation();
    ~RasterizationImplementation();
    void computeScreenCoordinates(const float &filmApertureWidth,
                                  const float &filmApertureHeight,
                                  const uint32_t &imageWidth,
                                  const uint32_t &imageHeight,
                                  const FitResolutionGate &fitFilm,
                                  const float &nearClippingPLane,
                                  const float &focalLength,
                                  float &top, float &bottom, float &left, float &right);
    void convertToRaster(const Vec3f &vertexWorld,
                         const Matrix44f &worldToCamera,
                         const float &l,
                         const float &r,
                         const float &t,
                         const float &b,
                         const float &near,
                         const uint32_t &imageWidth,
                         const uint32_t &imageHeight,
                         Vec3f &vertexRaster);
    
    std::list<glm::vec2> startRaster();
    
    float min3(const float &a, const float &b, const float &c);
    float max3(const float &a, const float &b, const float &c);
    float edgeFunction(const Vec3f &a, const Vec3f &b, const Vec3f &c);
    
};

#endif /* RasterizationImplementation_hpp */