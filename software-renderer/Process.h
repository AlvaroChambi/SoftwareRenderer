//
//  Process.h
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 14/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Process_h
#define Process_h

#include "Screen.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"

class Process
{
public:
    virtual void init(Screen* screen, Camera* camera ,Mesh* mesh, float delta){}
    virtual void render(Screen* screen, Camera* camera ,Mesh* mesh, float delta) = 0;
};

#endif /* Process_h */
