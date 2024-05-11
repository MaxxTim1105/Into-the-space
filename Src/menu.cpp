#include "menu.h"
#include "constants.h"

Menu::Menu(SDL_Renderer* renderer, TTF_Font* font) : renderer(renderer), font(font), mouseX(0), mouseY(0) {
    menuItems.push_back("Start Game");
    menuItems.push_back("Quit");
    // Tính toán vị trí các mục menu để căn giữa màn hình
    int totalMenuHeight = menuItems.size() * 30; // Giả sử mỗi mục menu có chiều cao 30 pixels
    int startY = (H - totalMenuHeight) / 2; // Tính toán vị trí bắt đầu để căn giữa theo trục y

    for (size_t i = 0; i < menuItems.size(); ++i) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, menuItems[i].c_str(), defaultColor);
        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        int yPos = static_cast<int>(startY) + static_cast<int>(i) * 50; // Ép kiểu giá trị startY và i * 50 thành kiểu int
        SDL_Rect rect = { (W - textWidth) / 2, yPos, textWidth, textHeight }; // Căn giữa theo trục x
        menuItemRects.push_back(rect);
        SDL_FreeSurface(textSurface);
    }
}

Menu::~Menu() {}

void Menu::render() {
    SDL_GetMouseState(&mouseX, &mouseY); // Lấy vị trí của chuột
    for (size_t i = 0; i < menuItems.size(); ++i) {
        SDL_Color color = defaultColor;
        if (menuItemRects[i].x <= mouseX && mouseX < menuItemRects[i].x + menuItemRects[i].w &&
            menuItemRects[i].y <= mouseY && mouseY < menuItemRects[i].y + menuItemRects[i].h) {
            color = hoverColor;
        }
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, menuItems[i].c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect dstRect = menuItemRects[i];
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(texture);
    }
}

MenuItem Menu::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&mouseX, &mouseY); // Cập nhật vị trí chuột khi có sự kiện di chuyển chuột
    }
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        for (size_t i = 0; i < menuItems.size(); ++i) {
            if (menuItemRects[i].x <= mouseX && mouseX < menuItemRects[i].x + menuItemRects[i].w &&
                menuItemRects[i].y <= mouseY && mouseY < menuItemRects[i].y + menuItemRects[i].h) {
                return static_cast<MenuItem>(i);
            }
        }
    }
    return MenuItem::START_GAME; // Giá trị mặc định
}
