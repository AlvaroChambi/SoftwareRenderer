//
//  RasterizationStage.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 15/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef RasterizationStage_hpp
#define RasterizationStage_hpp

#include <stdio.h>
#include "Process.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class RasterizationStage : public Process
{
public:
    RasterizationStage();
    ~RasterizationStage();
    void init(Screen* screen, Camera* camera ,Mesh* mesh, float delta);
    void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta);
private:
    
    glm::vec3 pointToRaster(glm::vec3 coord, glm::mat4 transformationMatrix)
    {
        glm::vec4 newCoord = glm::vec4(coord, 1.0f);
        glm::vec4 point = transformationMatrix * newCoord;
        int x = std::min(639, (int)((1 - point.x ) * 640*0.5) ) ;
        int y = std::min(479,(int)((1 + point.y) * 480*0.5f));
        int z = -point.z;
        return glm::vec3(x,y,z);
    }
    
    float min3(const float &a, const float &b, const float &c)
    { return std::min(a, std::min(b, c)); }
    
    float max3(const float &a, const float &b, const float &c)
    { return std::max(a, std::max(b, c)); }
    
    float edgeFunction(glm::vec3 a, glm::vec3 b, glm::vec3 c)
    { return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); }

};

#endif /* RasterizationStage_hpp */
