
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cmath>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <cstdlib>
#include <ctime>

using namespace std;

//window
const int width = 400;
const int height = 600;
int direct = 0 ;

SDL_Surface* surface=NULL;
SDL_Window* gwindow=NULL;
SDL_Renderer* render=NULL;
SDL_Texture * texture;
SDL_Texture * cltexture;
SDL_Texture * optexture;
TTF_Font *sfont;
SDL_Texture * wtexture;
SDL_Texture *wplaytexture;

SDL_Rect p_score = {35,0},p_play = {145,300};
int nscore = 0;
char cscore='0';

bool quit = false;
SDL_Event event;

//create window
void init();

void loadmedia();

//mane ha
SDL_Rect a,b,A,B;
const int rah=160;
void sakht_mane_a();
void sakht_mane_b();
void move_mane();
void show_mane();

//bird
SDL_Rect fix ={80,300,60,45};
void show_bird();
void move_bird();

void game_over();
void close();



int main(int argc, char *args[])
{
    srand(time(0));
    init();



    //keshidan avalin mane
    a.x = 350;
    a.h = rand() % 300;
    a.w = 40;
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &a);
    A.x = a.x;
    A.h = height;
    A.w = 40;
    A.y = a.h + rah;
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &A);

    b.x = 570;
    b.h = rand() % 400;
    b.w = 40;
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &b);
    B.x = b.x;
    B.h = height;
    B.w = 40;
    B.y = b.h + rah;
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &B);

    //neveshte ha
    sfont = TTF_OpenFont("font.ttf", 50);
    SDL_Color color = {255, 100, 100};
    SDL_Surface *write = TTF_RenderText_Solid(sfont, &cscore, color);
    wtexture = SDL_CreateTextureFromSurface(render, write);
    SDL_QueryTexture(wtexture, NULL, NULL, &p_score.w, &p_score.h);

    SDL_SetRenderDrawColor(render, 80, 90, 110, 0xFF);
    SDL_RenderClear(render);

    SDL_Color playcolor = {0,0,0};
    SDL_Surface *playwrite = TTF_RenderText_Solid(sfont,"play", playcolor);
    wplaytexture = SDL_CreateTextureFromSurface(render, playwrite);
    SDL_QueryTexture(wplaytexture, NULL, NULL, &p_play.w, &p_play.h);
    SDL_SetRenderDrawColor(render, 80, 40, 0, 0xFF);
    SDL_RenderFillRect(render, &p_play);
    SDL_RenderCopy(render, wplaytexture, NULL, &p_play);

    p_play={30,30};
    SDL_Color scolor = {0, 50, 0};
    SDL_Surface *swrite = TTF_RenderText_Solid(sfont, "SLEEPY BIRD :>", scolor);
    wplaytexture = SDL_CreateTextureFromSurface(render, swrite);
    SDL_QueryTexture(wplaytexture, NULL, NULL, &p_play.w, &p_play.h);
    SDL_RenderCopy(render, wplaytexture, NULL, &p_play);

    SDL_RenderPresent(render);
    
    SDL_Delay(1000);

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                return 0;
            }
            else if(event.type==SDL_KEYDOWN){
            switch(event.key.keysym.sym){
            case SDLK_SPACE:
            direct+=25;
            }


            }
        }

        if (fix.y == 552)
        {
            break;
        }

        //sakht dobarey mane
        if(a.x+a.w<0){
            sakht_mane_a();
        }
        else if(b.x+b.w<0){
            sakht_mane_b();
        }

        //bala bordan bird
        if(direct>0){
        fix.y-=5;
        direct--;
        }

        //collision a va b
        if (fix.x  + fix.w-10 >= a.x && fix.x <= a.x + a.w)
            if (fix.y <= a.h || fix.y + fix.h >= a.h + rah)
                fix.y = 550;

        if (fix.x + fix.w-10 >= b.x && fix.x <= b.x + b.w)
            if (fix.y <= b.h || fix.y + fix.h >= b.h + rah)
                fix.y = 550;

        //score
        if(fix.x == a.x || fix.x == b.x){
            nscore++;
            cscore= char (nscore + 48);
            write = TTF_RenderText_Solid(sfont, &cscore, color);
            wtexture = SDL_CreateTextureFromSurface(render, write);
           // cout<<cscore<<'\t'<<nscore<<'\n';
         
        }


        SDL_RenderCopy(render, texture, NULL, NULL);

        move_mane();
        show_mane();
        move_bird();
        show_bird();

        //awake bird
        if(direct>0)
            SDL_RenderCopy(render, optexture, NULL, &fix);

        //neveshte
        SDL_RenderCopy(render,wtexture,NULL,&p_score);


        SDL_RenderPresent(render);

        if(nscore>3){
            SDL_Delay(5);
        }else SDL_Delay(7);

        SDL_SetRenderDrawColor(render, 250, 250, 50, 0xFF);
        SDL_RenderClear(render);
    }
    game_over();
    SDL_Delay(6000);
    close();
    return 0 ;
    }


void init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    gwindow = SDL_CreateWindow("sleepy bird ;)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!gwindow)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
    }

    render = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
    if (!render)
    {
        printf("error creating renderer: %s\n", IMG_GetError());
        getchar();
        SDL_DestroyWindow(gwindow);
        SDL_Quit();
    }
    SDL_Surface * image = IMG_Load("IMG_۲۰۱۹۰۱۲۰_۱۰۱۴۳۱.png");
    texture = SDL_CreateTextureFromSurface(render, image);
    image = IMG_Load("sleepy.png");
    cltexture=SDL_CreateTextureFromSurface(render, image);
    image= IMG_Load("awake.png");
    optexture=SDL_CreateTextureFromSurface(render, image);
    SDL_FreeSurface(image);

    //sfont = TTF_OpenFont("font.ttf",50);
    //SDL_Color color = {255,0,0};
    //SDL_Surface *write = TTF_RenderText_Solid(sfont,&cscore,color);
    //wtexture = SDL_CreateTextureFromSurface(render,write);
    //SDL_QueryTexture(wtexture,NULL,NULL,&p_score.w,&p_score.h);
    //TTF_CloseFont(sfont);
}

void sakht_mane_a()
{
    a.x = width;
    a.h = rand() % 400;
    a.w = 40;

    SDL_SetRenderDrawColor(render, 0, 50, 0x00, 255);
    SDL_RenderFillRect(render, &a);

    A.x = a.x;
    A.h = height;
    A.w = 40;
    A.y = a.h+rah;
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &A);
}

void sakht_mane_b()
{
    b.x = width;
    b.h = rand() % 400;
    b.w = 40;

    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &b);

    B.x = b.x;
    B.h = height;
    B.w = 40;
    B.y = b.h + rah;

    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &B);
}

void move_mane()
{
    a.x-=1;
    A.x-=1;
    b.x-=1;
    B.x-=1;
}

void show_mane()
{
    SDL_SetRenderDrawColor(render, 0, 0, 50, 255);
    SDL_RenderFillRect(render, &a);
    SDL_RenderFillRect(render, &A);
    SDL_RenderFillRect(render, &b);
    SDL_RenderFillRect(render, &B);
}

void move_bird(){
fix.y+=2;


}

void show_bird()
{
    SDL_RenderCopy(render,cltexture,NULL,&fix);

}

void game_over()
{
    SDL_SetRenderDrawColor(render,70,70,70,255);
    SDL_RenderClear(render);

    SDL_Rect p_game={20,100},p_your = {20,250},p_score={220,250};

    SDL_Color playcolor = {0, 0, 0};
    SDL_Surface *gamewrite = TTF_RenderText_Solid(sfont, "GAME OVER :(", playcolor);
    wplaytexture = SDL_CreateTextureFromSurface(render, gamewrite);
    SDL_QueryTexture(wplaytexture, NULL, NULL, &p_game.w, &p_game.h);
    SDL_RenderCopy(render, wplaytexture, NULL, &p_game);

    sfont = TTF_OpenFont("font.ttf", 25);
    SDL_Surface *yourwrite = TTF_RenderText_Solid(sfont, "YOUR SCORE:", playcolor);
    wplaytexture = SDL_CreateTextureFromSurface(render, yourwrite);
    SDL_QueryTexture(wplaytexture, NULL, NULL, &p_your.w, &p_your.h);
    SDL_RenderCopy(render, wplaytexture, NULL, &p_your);

    SDL_Surface *swrite = TTF_RenderText_Solid(sfont, &cscore, playcolor);
    wplaytexture = SDL_CreateTextureFromSurface(render, swrite);
    SDL_QueryTexture(wplaytexture, NULL, NULL, &p_score.w, &p_score.h);
    SDL_RenderCopy(render, wplaytexture, NULL, &p_score);

    SDL_RenderPresent(render);
    SDL_Delay(1000);
}

void close()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(gwindow);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
