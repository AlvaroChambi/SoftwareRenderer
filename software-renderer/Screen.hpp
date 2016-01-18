//
//  Screen.hpp
//  software-renderer
//
//  Created by Alvaro Chambi Campos on 11/1/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "Color.h"
#include <glm/glm.hpp>

class Screen
{
public:
    Screen(int width, int height);
    ~Screen();
    void init();
    void clear(Color color);
    void drawPoint(glm::vec2 point, Color color);
    void present();
    int getWidth();
    int getHeight();
private:
    int width;
    int height;
    Uint32 * frameBuffer;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;
    void putPixel(int x, int y, Color color);
};

#endif /* Screen_hpp */
