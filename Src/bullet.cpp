
#include "bullet.h"
#include <cmath>
#include "constants.h"
bullet::bullet(SDL_Texture *tex) {
    name = "bullet";
    settings(new Animation(tex, 0, 0, 32, 64, 16, 0.8), 0, 0, 0, 10);
}

void bullet::update() {
    dx = cos(angle * DEGTORAD) * 6;
    dy = sin(angle * DEGTORAD) * 6;
    x += dx;
    y += dy;

    if (x > W || x < 0 || y > H || y < 0)
        life = false;
}
