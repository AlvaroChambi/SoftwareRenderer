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
    std::cin >> fileName;
    
    std::cout << "loading file..." << std::endl;
    return nullptr;
}

void projection()
{
    std::cout << "Projection stage." << std::endl;
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