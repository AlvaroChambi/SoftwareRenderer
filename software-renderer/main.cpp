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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include "Renderer.hpp"
#include "ProjectionStage.hpp"

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

void projection()
{
    std::cout << "Projection stage." << std::endl;
    Renderer* renderer = new Renderer();
    renderer->init();
    Process* process = new ProjectionStage();
    renderer->setProcess(process);
    renderer->startProcess();
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
                running = false;
                break;
            default:
                running = false;
                break;
        }
    }
    return 0;
}