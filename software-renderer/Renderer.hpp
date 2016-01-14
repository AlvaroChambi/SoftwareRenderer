//
//  Renderer.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 14/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include "Screen.hpp"
#include "Camera.hpp"
#include "Process.h"
#include "Mesh.hpp"

class Renderer
{
public:
    const int FPS = 30;
    const int DELAY_TIME = 1000.0f / FPS;
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;
    
    Renderer();
    ~Renderer();
    
    void setProcess(Process* process);
    void init();
    void startProcess();
private:
    Screen* screen;
    Camera* camera;
    Mesh* mesh;
    Process* process;
    bool running;
};

#endif /* Renderer_hpp */
