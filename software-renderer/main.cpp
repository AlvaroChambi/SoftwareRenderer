//
//  main.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 5/12/15.
//  Copyright © 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <SDL2/SDL.h> // include SDL header
#include <iostream>
#include <glm/glm.hpp>
#include "Camera.hpp"
#include "Mesh.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>

const int FPS = 30;
const int DELAY_TIME = 1000.0f / FPS;

typedef unsigned char byte;

int foo()
{
    glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
    glm::mat4 Model = glm::mat4(1.0);
    Model[3] = glm::vec4( 1.0, 1.0, 0.0, 1.0 );
    glm::vec4 Transformed = Model * Position;
    return 0;
}

struct Color{
    byte r;
    byte g;
    byte b;
    byte a;
};

Mesh* buildCude()
{
    Mesh* mesh = new Mesh();
    std::vector<glm::vec3> vertices(8);
    vertices[0] = glm::vec3(-1,1,1);
    vertices[1] = glm::vec3(1,1,1);
    vertices[2] = glm::vec3(-1,-1,1);
    vertices[3] = glm::vec3(-1,-1,-1);
    vertices[4] = glm::vec3(-1,1,-1);
    vertices[5] = glm::vec3(1,1,-1);
    vertices[6] = glm::vec3(1,-1,1);
    vertices[7] = glm::vec3(1,-1,-1);
    mesh->setVertices(vertices);

    return mesh;
}

void clear(byte r, byte g, byte b, byte a, Uint32* buffer, int size)
{
    for (Uint32 i = 0; i < size; i++) {
        Uint32 ulTotal = r;
        ulTotal = (ulTotal  << 8) + g;
        ulTotal = (ulTotal  << 8) + b;
        ulTotal = (ulTotal  << 8) + a;
        
        buffer[i]= ulTotal;
    }
}

void putPixel(int x, int y, Color color, Uint32* pixels)
{
    Uint32 ulTotal = color.r;
    ulTotal = (ulTotal  << 8) + color.g;
    ulTotal = (ulTotal  << 8) + color.b;
    ulTotal = (ulTotal  << 8) + color.a;
    
    pixels[x + (y * 640)] = ulTotal;
}

void drawPoint(glm::vec2 point, Uint32* pixels)
{
    Color red;
    red.r = 255;
    red.g = 255;
    red.b = 255;
    red.a = 255;
    
    if (point.x >= 0 && point.y >= 0 && point.x < 640 && point.y < 480) {
        putPixel(point.x, point.y, red, pixels);
    }
}

glm::vec2 project(glm::vec3 coord, glm::mat4 transformationMatrix)
{
    glm::vec4 newCoord = glm::vec4(coord, 1.0f);
    glm::vec4 point = transformationMatrix * newCoord;
    int x = (float)640/2 - point.x;
    int y = (float)480/2 - point.y;
    
    return glm::vec2(x,y);
}

void render(Camera* camera, std::list<Mesh*> meshes, Uint32* pixels, float increment)
{
    glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(),
                                 camera->getTarget(),
                                 glm::vec3(0.0f, 1.0f, 0.0f)
                                 );
    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 1.0f);
    for (Mesh* mesh : meshes) {
        glm::mat4 translationMatrix = glm::translate(mesh->getPosition());
        glm::mat4 rotationMatrix = glm::rotate(increment * 10.0f, glm::vec3(1.0f,1.0f,0.0f));
        glm::mat4 worldMatrix = translationMatrix * rotationMatrix;
        //worldMatrix = glm::rotate(worldMatrix,20.0f, glm::vec3(1.0f,0.0f,0.0f));
        glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * worldMatrix;
        for (glm::vec3 vector : mesh->getVertices()) {
            glm::vec2 point = project(vector, transformationMatrix);
            drawPoint(point, pixels);
        }
    }
}

int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;
    
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture * texture = SDL_CreateTexture(renderer,
                                              SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
    Uint32 * pixels = new Uint32[640 * 480];
    Camera* camera = new Camera;
    camera->setTarget(glm::vec3(0,0,0));
    camera->setPosition(glm::vec3(0,0,10));
    Mesh* mesh = buildCude();
    std::list<Mesh*> meshes;
    meshes.push_back(mesh);
    float increment = 0;
    
    Uint32 frameStart, frameTime;
    while (!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        frameStart = SDL_GetTicks();
    
        increment+=0.1f;
        clear(0, 0,0, 0, pixels, 640*480);
        render(camera, meshes, pixels,increment);
        SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime < DELAY_TIME){
            SDL_Delay(DELAY_TIME - frameTime);
        }

    }
    
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}