//
//  Screen.cpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 11/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#include "Screen.hpp"

Screen::Screen(int width, int height)
{
    this->width = width;
    this->height = height;
    
    frameBuffer = new Uint32[width * height];
}

Screen::~Screen()
{
    delete[] frameBuffer;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Screen::init()
{
    window = SDL_CreateWindow("Rendering since 2016",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
}

void Screen::clear(Color color)
{
    for (Uint32 i = 0; i < width*height ; i++) {
        Uint32 ulTotal = color.r;
        ulTotal = (ulTotal  << 8) + color.g;
        ulTotal = (ulTotal  << 8) + color.b;
        ulTotal = (ulTotal  << 8) + color.a;
        
        frameBuffer[i]= ulTotal;
    }
}

void Screen::drawPoint(glm::vec2 point, Color color)
{
    if (point.x >= 0 && point.y >= 0 && point.x < 640 && point.y < 480) {
        putPixel(point.x, point.y, color);
    }
}

void Screen::putPixel(int x, int y, Color color)
{
    Uint32 ulTotal = color.r;
    ulTotal = (ulTotal  << 8) + color.g;
    ulTotal = (ulTotal  << 8) + color.b;
    ulTotal = (ulTotal  << 8) + color.a;
    
    frameBuffer[x + (y * width)] = ulTotal;
}

void Screen::present()
{
    SDL_UpdateTexture(texture, NULL, frameBuffer, width * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

}

