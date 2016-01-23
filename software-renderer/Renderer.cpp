//
//  Renderer.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 14/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer() :
    running(true),
    screen(nullptr),
    camera(nullptr),
    mesh(nullptr)
{

}

Renderer::~Renderer()
{

}

void Renderer::init()
{
    screen = new Screen(WINDOW_WIDTH, WINDOW_HEIGHT);
    camera = new Camera;
    camera->setTarget(glm::vec3(0,0,0));
    camera->setPosition(glm::vec3(0,0,10));
    mesh = new Mesh();
    mesh->loadObj("/Users/achambi/Development/Software Renderer/software-renderer/cube.obj");
    screen->init();

}

void Renderer::startProcess()
{
    Uint32 frameStart, frameTime;
    float delta = 0;
    process->init(screen, camera, mesh, delta);
    
    bool onClickDown = false;
    Event* gameEvent = new Event;
    while (running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEMOTION:
                    if (onClickDown) {
                        gameEvent->type = ON_MOUSE_DRAG;
                        gameEvent->x = event.motion.x;
                        gameEvent->y = event.motion.y;
                        
                        gameEvent->xRelative = event.motion.xrel;
                        gameEvent->yRelative = event.motion.yrel;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    gameEvent->type = ON_MOUSE_DOWN_EVENT;
                    gameEvent->x = event.motion.x;
                    gameEvent->y = event.motion.y;
                    onClickDown = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    onClickDown = false;
                    break;
                case SDL_MOUSEWHEEL:
                    gameEvent->type = ON_MOUSEWHEEL;
                    gameEvent->xMousewheel = event.wheel.x;
                    gameEvent->yMousewheel = event.wheel.y;
                    break;
            }
        }
        delta+=0.1f;
        frameStart = SDL_GetTicks();
        screen->clear(Color(0,0,0));
        process->render(screen, camera, mesh, delta, gameEvent);
        screen->present();
        
        frameTime = SDL_GetTicks() - frameStart;
        std::cout << "frame time: " << frameTime << std::endl;
        if(frameTime < DELAY_TIME){
            SDL_Delay(DELAY_TIME - frameTime);
        }
        
    }
}

void Renderer::setProcess(Process *process)
{
    this->process = process;
}
