#include <SDL.h>
#include <fstream>
#include <iostream>
#include "GameShell.h"

GameShell::GameShell()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("sdl-alg-sd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);// | SDL_WINDOW_FULLSCREEN);
    screen = SDL_GetWindowSurface(window);
    background = SDL_LoadBMP("cs2dnorm.bmp");
}

GameShell::~GameShell()
{
    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameShell::refresh()
{
    SDL_UpdateWindowSurface(window);
}

void GameShell::parse()
{
    SDL_Rect tiles[3];
    SDL_Rect srctile, destile;
    std::ifstream mapfile("map.txt");
    int nr;

    tiles[0].y = tiles[1].y = 0 * TILE_HEIGHT;
    tiles[0].x = 10 * TILE_WIDTH;
    tiles[1].x = 11 * TILE_WIDTH;
    tiles[2].x = 14 * TILE_WIDTH;
    tiles[2].y = 6 * TILE_HEIGHT;

    for (int i = 0; i < 3; i++)
    {
        tiles[i].w = TILE_WIDTH;
        tiles[i].h = TILE_HEIGHT;
    }

    destile.x = -TILE_WIDTH;
    destile.y = 0;
    while(mapfile >> nr)
    {
        //harta.push_back(nr);
        srctile = tiles[nr];
        destile.x += TILE_WIDTH;
        SDL_BlitSurface(background, &srctile, screen, &destile);
        if(destile.x >= SCREEN_WIDTH - TILE_WIDTH)
        {
            destile.y += TILE_WIDTH;
            destile.x = -TILE_WIDTH;
        }
    }
    SDL_UpdateWindowSurface(window);
    mapfile.close();
}

void GameShell::loadMap()
{
    SDL_Rect srctile, destile;
    srctile.y = 5 * TILE_HEIGHT;
    srctile.w = srctile.h = TILE_HEIGHT;

    for (int i = 0; i < SCREEN_WIDTH / TILE_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT / TILE_HEIGHT; j++)
        {
            if ((i + j) % 2)
                srctile.x =  5 * TILE_WIDTH;
            else
                srctile.x = 4 * TILE_WIDTH;

            destile.x = i * TILE_WIDTH;
            destile.y = j * TILE_HEIGHT;
            SDL_BlitSurface(background, &srctile, screen, &destile);
        }
    }
    SDL_UpdateWindowSurface(window);
}

void GameShell::repaintTile(SDL_Rect coord)
{
    SDL_Rect srctile;
    srctile.y = 5 * TILE_HEIGHT;
    srctile.w = srctile.h = TILE_HEIGHT;
    if(((coord.x / TILE_WIDTH) + (coord.y / TILE_HEIGHT)) % 2)
    {
        srctile.x = 5 * TILE_WIDTH;
    }
    else
    {
        srctile.x = 4 * TILE_WIDTH;
    }
    SDL_BlitSurface(background, &srctile, screen, &coord);
}
