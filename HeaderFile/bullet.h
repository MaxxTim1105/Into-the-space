#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"
class bullet:public Entity{
public:
    bullet(SDL_Texture *tex);
    void update() override;
};
#endif 
