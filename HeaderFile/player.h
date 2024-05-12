#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class player:public Entity{
public:
    bool thrust;

    player(SDL_Texture *tex);
    void update() override;
};
#endif 
