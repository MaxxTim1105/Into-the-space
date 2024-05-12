#include "Animation.h"

Animation::Animation(SDL_Texture *tex, int x, int y, int w, int h, int count, float Speed){
    Frame=0;
    speed=Speed;
    texture=tex;
    for (int i=0;i<count;i++)
        frames.push_back({x+i * w, y, w, h});
}
void Animation::update() {
    Frame+=speed;
    int n=frames.size();
    if (Frame>=n)
        Frame-=n;
}
