#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <vector>

class Animation {
public:
    float Frame, speed;
    SDL_Texture *texture;
    std::vector<SDL_Rect> frames;

    Animation(SDL_Texture *tex, int x, int y, int w, int h, int count, float Speed);
    void update();
};

#endif 
