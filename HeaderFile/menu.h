#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
//các chữ trên menu
enum MenuItem {
    START_GAME,
    QUIT
};

class Menu {
public:
    Menu(SDL_Renderer* renderer, TTF_Font* font);
    ~Menu();
    void render();
    MenuItem handleEvent(SDL_Event& e);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::vector<std::string> menuItems;
    std::vector<SDL_Rect> menuItemRects;
    const SDL_Color defaultColor = { 255, 255, 255 }; //màu mặc định là trắng
    const SDL_Color hoverColor = { 255, 0, 0 }; //chuột trên chữ thì đổi màu đỏ
    int mouseX;//các vị trí
    int mouseY; //của mouse
};

#endif 
