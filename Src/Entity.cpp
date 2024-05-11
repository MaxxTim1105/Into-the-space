#include "Entity.h"
#include "constants.h"
Entity::Entity() {}

void Entity::settings(Animation *a, float X, float Y, float Angle, int radius) {
    anim = a;
    x = X;
    y = Y;
    angle = Angle;
    R = radius;
    life = true;

}

void Entity::update() {
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

void Entity::draw(SDL_Renderer *renderer) {
    SDL_Rect dstRect = {(int)(x - anim->frames[0].w / 2), (int)(y - anim->frames[0].h / 2), anim->frames[0].w, anim->frames[0].h};
    SDL_RenderCopyEx(renderer, anim->texture, &anim->frames[(int)anim->Frame], &dstRect, angle + 90, nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 170);
    SDL_RenderDrawPoint(renderer, (int)x, (int)y);
}

Entity::~Entity() {}
