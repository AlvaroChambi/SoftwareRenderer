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
#include "Color.h"
#include "Screen.hpp"

const int FPS = 30;
const int DELAY_TIME = 1000.0f / FPS;
const int LOAD_OBJ = 1;
const int PROJECTION = 2;
const int RASTERIZATION = 3;

std::list<std::pair<int, std::string>> getMenu()
{
    std::list<std::pair<int, std::string>> mainMenu;
    std::pair<int, std::string> loadObjFile = std::make_pair(LOAD_OBJ,"Load an .obj file");
    std::pair<int, std::string> perspectiveProjection = std::make_pair(PROJECTION, "Perspective projection");
    std::pair<int, std::string> rasterizationStage = std::make_pair(RASTERIZATION, "Rasterization stage");
    
    mainMenu.push_back(loadObjFile);
    mainMenu.push_back(perspectiveProjection);
    mainMenu.push_back(rasterizationStage);
    
    return mainMenu;
}

int getSelectedOption()
{
    std::cout << "Select an option: ";
    int option;
    std::cin >> option;
    return option;
}

void printMenu(std::list<std::pair<int, std::string>> menu)
{
    std::string separator = ".- ";
    for (std::pair<int, std::string> item : menu) {
        std::cout << item.first << separator << item.second << std::endl;
    }
}

Mesh* loadObj()
{
    std::cout << ".obj path: ";
    std::string fileName;
    std::cin.ignore();
    std::getline(std::cin, fileName);
    Mesh* mesh = new Mesh;
    std::cout << "loading file..." << std::endl;
    mesh->loadObj(fileName);
    std::cout << "Mesh loaded succesfully!" << std::endl;
    return mesh;
}

glm::vec2 project(glm::vec3 coord, glm::mat4 transformationMatrix)
{
    glm::vec4 newCoord = glm::vec4(coord, 1.0f);
    glm::vec4 point = transformationMatrix * newCoord;
    int x = (float)640/2 - point.x;
    int y = (float)480/2 - point.y;
    
    return glm::vec2(x,y);
}

void render(Camera* camera, Mesh* mesh, float increment, Screen* screen)
{
    glm::mat4 viewMatrix = glm::lookAt(camera->getPosition(),
                                       camera->getTarget(),
                                       glm::vec3(0.0f, 1.0f, 0.0f)
                                       );
    glm::mat4 projectionMatrix = glm::perspective(0.78f, (float)640/480, 0.01f, 1.0f);

    glm::mat4 translationMatrix = glm::translate(mesh->getPosition());
    glm::mat4 rotationMatrix = glm::rotate(increment * 1.0f, glm::vec3(1.0f,1.0f,0.0f));
    glm::mat4 scaleMatrix = glm::scale(glm::vec3(20,20,20));
    glm::mat4 worldMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glm::mat4 transformationMatrix = projectionMatrix * viewMatrix * worldMatrix;
    for (glm::vec3 vector : mesh->getVertices()) {
        glm::vec2 point = project(vector, transformationMatrix);
        screen->drawPoint(point, Color(255,255,255));
    }
}

void projection()
{
    std::cout << "Projection stage." << std::endl;
    
    bool quit = false;
    Uint32 frameStart, frameTime;
    Screen* screen = new Screen(640, 480);
    Camera* camera = new Camera;
    camera->setTarget(glm::vec3(0,0,0));
    camera->setPosition(glm::vec3(0,0,10));
    Mesh* mesh = new Mesh();
    mesh->loadObj("cube.obj");
    screen->init();
    
    float increment = 0;
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
        screen->clear(Color(0,0,0));
        render(camera, mesh, increment, screen);
        screen->present();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime < DELAY_TIME){
            SDL_Delay(DELAY_TIME - frameTime);
        }
        
    }
}

void rasterizationStage()
{
    std::cout << "Rasterization stage" << std::endl;
}

int main(int argc, char ** argv)
{
    bool running = true;
    printMenu(getMenu());
    while(running){
        switch (getSelectedOption()) {
            case LOAD_OBJ:
                loadObj();
                break;
            case PROJECTION:
                projection();
                running = false;
                break;
            case RASTERIZATION:
                rasterizationStage();
                break;
            default:
                running = false;
                break;
        }
    }
    return 0;
}