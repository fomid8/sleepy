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

SDL_Surface* surface=NULL;
SDL_Window* gwindow=NULL;
SDL_Renderer* render=NULL;
bool quit = false;
SDL_Event event;

//create window
void init();

//mane ha
SDL_Rect a,b,A,B;
const int fasele=width/2;
const int rah=100;
void sakht_mane_a();
void sakht_mane_b();
void move_mane();
void show_mane();

void close();


int main(int argc, char *args[])
{
    srand(time(0));
    init();

    SDL_SetRenderDrawColor(render, 250, 250, 50, 0xFF);
    SDL_RenderClear(render);

    //keshidan avalin mane
    a.x = fasele;
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

    sakht_mane_b();
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

        if(a.x+a.w<0){
            sakht_mane_a();
        }
        else if(b.x+b.w<0){
            sakht_mane_b();
        }

        move_mane();
        show_mane();

        SDL_RenderPresent(render);
        SDL_Delay(5);

        SDL_SetRenderDrawColor(render, 250, 250, 50, 0xFF);
        SDL_RenderClear(render);
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

void sakht_mane_a()
{
    a.x = width;
    a.h = rand() % 500;
    a.w = 40;

    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
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
    b.h = rand() % 500;
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
    SDL_SetRenderDrawColor(render, 50, 0x00, 0x00, 255);
    SDL_RenderFillRect(render, &a);
    SDL_RenderFillRect(render, &A);
    SDL_RenderFillRect(render, &b);
    SDL_RenderFillRect(render, &B);
}

void close()
{

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(gwindow);
    IMG_Quit();
    SDL_Quit();
}