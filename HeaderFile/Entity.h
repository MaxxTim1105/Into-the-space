#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "Animation.h"
#include <string>

class Entity{
public:
    float x, y, dx, dy, R, angle;
    bool life;
    std::string name;
    Animation *anim;

    Entity();
    virtual void settings(Animation *a, float X, float Y, float Angle = 0, int radius = 1);
    virtual void update();
    void draw(SDL_Renderer *renderer);
    virtual ~Entity();
};
#endif
