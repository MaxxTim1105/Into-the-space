#include "asteroid.h"
#include "constants.h"
asteroid::asteroid(SDL_Texture *tex){
    dx=rand()%8-4;
    dy=rand()%8-4;
    name="asteroid";
    settings(new Animation(tex, 0, 0, 64, 64, 16, 0.2), rand()%W, rand()%H, rand()%360, 25);
}

void asteroid::update() {
    x+=dx;
    y+=dy;
    if (x>W) x=0;
    if (x<0) x=W;
    if (y>H) y=0;
    if (y<0) y=H;
}
