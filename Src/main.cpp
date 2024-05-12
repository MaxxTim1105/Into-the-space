#include "../HeaderFile/stdafx.h"
#undef main
using namespace std;
enum GameState {
    MENU,
    GAME,
    GAME_OVER
};
//xử lý va chạm
bool isCollide(Entity *a, Entity *b)
{
    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) < (a->R + b->R) * (a->R + b->R);
}

int main()
{
    srand(time(0));
    //xử lý lỗi và khởi tạo window, 
    if (TTF_Init()!=0){
        cerr<<"font error: "<<TTF_GetError()<<endl;
        return 1;
    }
    if (SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        cerr<<"SDL error: "<<SDL_GetError()<<endl;
        return 1;
    }
    SDL_Window *window =SDL_CreateWindow("Into the space", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
    if (window==nullptr)
    {
        cerr<<"fail to create window: "<<SDL_GetError()<<endl;
        SDL_Quit();
        return 1;
    }
    SDL_SetWindowBordered(window, SDL_TRUE);
    SDL_Renderer *renderer= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer==nullptr)
    {
        cerr<<"error: "<<SDL_GetError()<<endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font =TTF_OpenFont("font.ttf", 36);//font của menu
    if (font==nullptr){
        cerr<<"TTF_OpenFont Error: "<<TTF_GetError()<<endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    TTF_Font* font2= TTF_OpenFont("font.ttf", 18); //font của highscore
    SDL_Texture* scoreTexture=nullptr;  
    SDL_Texture* highScoreTexture=nullptr;
    HighScoreManager highScoreManager("highscore.txt"); //mở file highscore để đọc và ghi
    Uint32 startTime=0;
    int score = 0;
    // Tạo menu
    Menu menu(renderer, font);
    //chuyển ảnh game thành các texture
    SDL_Texture *t1=IMG_LoadTexture(renderer, "images/spaceship.png");
    SDL_Texture *t2=IMG_LoadTexture(renderer, "images/background.jpg");
    SDL_Texture *t3=IMG_LoadTexture(renderer, "images/explosions/type_C.png");
    SDL_Texture *t4=IMG_LoadTexture(renderer, "images/rock.png");
    SDL_Texture *t5=IMG_LoadTexture(renderer, "images/fire_red.png");
    SDL_Texture *t6=IMG_LoadTexture(renderer, "images/rock_small.png");
    SDL_Texture *t7=IMG_LoadTexture(renderer, "images/explosions/type_B.png");
    //xử lý lỗi
    if (t1==nullptr||t2==nullptr||t3==nullptr||t4==nullptr||t5==nullptr ||t6==nullptr ||t7==nullptr){
        cerr << "error: "<<SDL_GetError()<<endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //tạo vector lưu trữ các đối tượng
    vector<Entity*> entities;
    //tạo trước thiên thạch cho đỡ trống :))
    for (int i=0;i<8;i++)
    {
        entities.push_back(new asteroid(t4));
    }
    GameState gameState=MENU;//set mặc định trạng thái của game là ở menu
    SDL_Event event;//tạo đối tượng event để xử lý chuột
    bool quit =false; //flag để loop game
    player *p =nullptr; //player để sử dụng 1 lần duy nhất
    Uint32 lastFireTime=0; //đánh dấu thời điểm đạn bắn 
    while(!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type==SDL_QUIT) quit=true;                
            if (gameState==MENU)
            {
                if (event.type==SDL_MOUSEMOTION)
                {
                    //cập nhật vị trí chuột 
                    menu.handleEvent(event);
                }
                else if (event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
                {
                    MenuItem menuItem=menu.handleEvent(event);
                    if (menuItem==START_GAME)
                    {
                        gameState=GAME;
                        startTime=SDL_GetTicks();//lấy thời gian bắt đầu game đẻ tính điểm
                        score=0; // Reset điểm
                        //cấp phát bộ nhớ cho player khi chuyển trạng thái sang start game
                        p=new player(t1);
                        entities.push_back(p);
                    }
                    else if(menuItem==QUIT)
                    {
                        quit=true;
                    }
                }
            }
        }

        if (gameState==GAME)//xử lý trạng thái start game
        {
            Uint32 currentTime=SDL_GetTicks();
            score=(currentTime-startTime)/1000; //tính điểm
            if (score>highScoreManager.getHighScore())//cập nhật highscore
            {
                highScoreManager.updateHighScore(score);
            }
            // Xử lý di chuyển của ship
            const Uint8 *state=SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_SPACE]&& currentTime-lastFireTime>FIRE_RATE){
                bullet *b=new bullet(t5);
                b->settings(new Animation(t5, 0, 0, 32, 64, 16, 0.8), p->x, p->y, p->angle, 10);
                entities.push_back(b);
                lastFireTime=currentTime; //thời gian bắn đạn lần cuối để giới hạn firerate
            }
            //các phím di chuyển
            if (state[SDL_SCANCODE_RIGHT]) p->angle+=3;
            if (state[SDL_SCANCODE_LEFT]) p->angle-=3;
            if (state[SDL_SCANCODE_UP])
                p->thrust=true;
            else
                p->thrust=false;
            //xử lý va chạm
            for (auto a:entities)
            {
                for (auto b:entities)
                {
                    if (a->name=="asteroid" && b->name =="bullet")
                    {
                        if (isCollide(a, b))
                        {
                            a->life=false;
                            b->life=false;
                            Entity *e=new Entity();
                            e->settings(new Animation(t3, 0, 0, 256, 256, 48, 0.5), a->x, a->y);
                            e->name="explosion";
                            entities.push_back(e);
                            for (int i=0;i<2;i++)//thiên thạch lớn nổ ra 2 cái nhỏ
                            {
                                if (a->R ==15)
                                    continue;
                                Entity *e =new asteroid(t6);
                                e->settings(new Animation(t6, 0, 0, 64, 64, 16, 0.2), a->x, a->y, rand() % 360, 15);
                                entities.push_back(e);
                            }
                        }
                    }

                    if (a->name=="player" && b->name=="asteroid")
                    {
                        if (isCollide(a, b))
                        {
                            b->life=false;
                            Entity *e=new Entity();
                            e->settings(new Animation(t7, 0, 0, 192, 192, 64, 0.5), a->x, a->y);
                            e->name="explosion";
                            entities.push_back(e);
                            //chết thì rs lại vị trí của ship
                            p->settings(new Animation(t1, 40, 0, 40, 40, 1, 0), W / 2, H / 2, 0, 20);
                            p->dx=0;
                            p->dy=0;
                            gameState=GAME_OVER;
                        }
                    }
                }
            }
            //nếu tàu di chuyển thì dùng animation khác
            if (p->thrust)
                p->anim=new Animation(t1, 40, 40, 40, 40, 1, 0);
            else
                p->anim=new Animation(t1, 40, 0, 40, 40, 1, 0);
            //Xử lý frames của vụ nổ
            for (auto e:entities)
            {
                if (e->name=="explosion")
                {
                    if (e->anim->Frame >= e->anim->frames.size()-1)
                        e->life=false;
                }
            }
            //tạo thiên thạch
            if (rand()%90==0)
            {
                asteroid *a=new asteroid(t4);
                a->settings(new Animation(t4, 0, 0, 64, 64, 16, 0.2), 0, rand()%H, rand()%360, 25);
                entities.push_back(a);
            }
            //cập nhật animation entities
            for (auto i=entities.begin();i!=entities.end();)
            {
                Entity *e=*i;
                e->update();
                e->anim->update();
                if (!e->life)
                {
                    i=entities.erase(i);
                    delete e;
                }
                else
                    i++;
            }
        }
        // Chết thì chuyển về menu
        if (gameState==GAME_OVER)
        {
            entities.clear(); // xoá các entities
            p->settings(new Animation(t1, 40, 0, 40, 40, 1, 0), W/2, H/2, 0, 20);//rs vị trí của player
            p->dx=0;
            p->dy=0;
            gameState=MENU;
        }
        SDL_RenderClear(renderer);
        if (gameState==MENU){
            SDL_RenderCopy(renderer, t2, NULL, NULL); //hiển thị background
            menu.render(); // Hiển thị menu
        } else {
            SDL_RenderCopy(renderer, t2, NULL, NULL);
            for (auto i :entities)
                i->draw(renderer); 
            // Hiển thị điểm số
            string scoreText="Score: "+to_string(score);
            SDL_Surface* scoreSurface=TTF_RenderText_Solid(font2, scoreText.c_str(),{255, 255, 255}); // Màu trắng
            scoreTexture=SDL_CreateTextureFromSurface(renderer, scoreSurface);
            SDL_Rect scoreRect={20, 40, scoreSurface->w, scoreSurface->h};
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
            SDL_FreeSurface(scoreSurface);
            // Hiển thị high score
            string highScoreText="High Score: "+to_string(highScoreManager.getHighScore());
            SDL_Surface* highScoreSurface=TTF_RenderText_Solid(font2, highScoreText.c_str(), {255, 255, 255});
            highScoreTexture=SDL_CreateTextureFromSurface(renderer, highScoreSurface);
            SDL_Rect highScoreRect={20, 62, highScoreSurface->w, highScoreSurface->h};
            SDL_RenderCopy(renderer, highScoreTexture, NULL, &highScoreRect);
            SDL_FreeSurface(highScoreSurface);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect closeButton={ W - 30, 0, 30, 30 };
            SDL_RenderFillRect(renderer, &closeButton);
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(1000/60);
    }
    //giải phóng bộ nhớ
    for (auto i :entities) delete i;
    SDL_DestroyTexture(t1);
    SDL_DestroyTexture(t2);
    SDL_DestroyTexture(t3);
    SDL_DestroyTexture(t4);
    SDL_DestroyTexture(t5);
    SDL_DestroyTexture(t6);
    SDL_DestroyTexture(t7);
    SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(highScoreTexture); 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
