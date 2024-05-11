#ifndef ASTEROID_H
#define ASTEROID_H

#include "Entity.h"

class asteroid : public Entity {
public:
    asteroid(SDL_Texture *tex);
    void update() override;
};

#endif 
