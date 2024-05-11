
#include "player.h"
#include <cmath>
#include "constants.h"
player::player(SDL_Texture *tex) {
    name = "player";
    settings(new Animation(tex, 40, 0, 40, 40, 1, 0), W / 2, H / 2, 0, 20);
}

void player::update() {
    if (thrust) {
        dx += cos(angle * DEGTORAD) * 0.2;
        dy += sin(angle * DEGTORAD) * 0.2;
    } else {
        dx *= 0.99;
        dy *= 0.99;
    }

    float maxSpeed = 8;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed) {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W)
        x = 0;
    if (x < 0)
        x = W;
    if (y > H)
        y = 0;
    if (y < 0)
        y = H;
}
