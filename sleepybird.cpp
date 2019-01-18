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

const int width = 400;
const int height = 600;
SDL_Surface* surface=NULL;
SDL_Window* gwindow=NULL;
SDL_Renderer* render=NULL;
bool quit = false;
SDL_Event event;

void init();
void sakht_mane();
//void move_mane;
//void show_mane;
void close();

struct mane
{
    int x=200;
    int y1=0;
    int height;
    int width=40;
    int height2;
    int y2;
};

mane a,b,c;

int main(int argc, char *args[])
{
    srand(time(0));
    init();
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                return 0;
            }
        }
        //SDL_SetRenderDrawColor(render, 250, 250, 50, 0xFF);
        //SDL_RenderClear(render);

        //filledPolygonColor()
        sakht_mane();

        SDL_RenderPresent(render);
        SDL_Delay(1000);
    }
    close();
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

  
}

void sakht_mane()
{
    a.height=rand()%300;

    SDL_Rect fillRect1 = {a.x,a.y1, a.width, a.height};

    SDL_Rect fillRect2 = {100, a.y1, a.width, a.height};
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &fillRect1);
    SDL_RenderFillRect(render, &fillRect2);
}

void close()
{

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(gwindow);
    IMG_Quit();
    SDL_Quit();
}