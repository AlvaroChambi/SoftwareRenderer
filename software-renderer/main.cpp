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
#include "RasterizationStage.hpp"
#include "ScratchPixelTriangleRaster.hpp"
#include "ScratchPixelRaster3D.hpp"
#include "DepthBufferRasterization.hpp"

const int LOAD_OBJ = 1;
const int PROJECTION = 2;
const int RASTERIZATION = 3;
const int SCRATCH_PIXEL_TRIANGLE_RASTER = 4;
const int SCRATCH_PIXEL_3DRASTER = 5;
const int RASTERIZATION_DEPTH_BUFFER = 6;

std::list<std::pair<int, std::string>> getMenu()
{
    std::list<std::pair<int, std::string>> mainMenu;
    std::pair<int, std::string> loadObjFile = std::make_pair(LOAD_OBJ,"Load an .obj file");
    std::pair<int, std::string> perspectiveProjection = std::make_pair(PROJECTION, "Perspective projection");
    std::pair<int, std::string> rasterizationStage = std::make_pair(RASTERIZATION, "Rasterization stage");
    std::pair<int, std::string> scratchPixelTriangleRaster = std::make_pair(SCRATCH_PIXEL_TRIANGLE_RASTER, "Scratch pixel triangle raster");
    std::pair<int, std::string> scratchPixel3DRaster = std::make_pair(SCRATCH_PIXEL_3DRASTER, "Scratch pixel Raster 3D");
    std::pair<int, std::string> rasterDepthBuffer = std::make_pair(RASTERIZATION_DEPTH_BUFFER, "Rasterization with depth buffer");
    
    mainMenu.push_back(loadObjFile);
    mainMenu.push_back(perspectiveProjection);
    mainMenu.push_back(rasterizationStage);
    mainMenu.push_back(scratchPixelTriangleRaster);
    mainMenu.push_back(scratchPixel3DRaster);
    mainMenu.push_back(rasterDepthBuffer);
    
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

void projection(Renderer* renderer)
{
    renderer->init();
    Process* process = new ProjectionStage();
    renderer->setProcess(process);
    renderer->startProcess();
}

void rasterizationStage(Renderer* renderer)
{
    renderer->init();
    Process* process = new RasterizationStage;
    renderer->setProcess(process);
    renderer->startProcess();
}

void scratchPixelTriangleRender(Renderer* renderer)
{
    renderer->init();
    Process* process = new ScratchPixelTriangleRaster;
    renderer->setProcess(process);
    renderer->startProcess();
}

void scratchPixel3DRaster(Renderer* renderer)
{
    renderer->init();
    Process* process = new ScratchPixelRaster3D;
    renderer->setProcess(process);
    renderer->startProcess();
}

void rasterWithDetphBuffer(Renderer* renderer)
{
    renderer->init();
    Process* process = new DepthBufferRasterization;
    renderer->setProcess(process);
    renderer->startProcess();
}

int main(int argc, char ** argv)
{
    bool running = true;
    Renderer* renderer = new Renderer();
    printMenu(getMenu());
    while(running){
        switch (getSelectedOption()) {
            case LOAD_OBJ:
                loadObj();
                break;
            case PROJECTION:
                projection(renderer);
                running = false;
                break;
            case RASTERIZATION:
                rasterizationStage(renderer);
                running = false;
                break;
            case SCRATCH_PIXEL_TRIANGLE_RASTER:
                scratchPixelTriangleRender(renderer);
                running = false;
                break;
            case SCRATCH_PIXEL_3DRASTER:
                scratchPixel3DRaster(renderer);
                running = false;
                break;
            case RASTERIZATION_DEPTH_BUFFER:
                rasterWithDetphBuffer(renderer);
                running = false;
                break;
            default:
                running = false;
                break;
        }
    }
    return 0;
}