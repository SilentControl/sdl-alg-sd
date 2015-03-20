#include "Enemy.h"
#include "GameShell.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

Enemy::Enemy(){
    image = SDL_LoadBMP("zombie.bmp");
    position = {0, 0, TILE_HEIGHT, TILE_WIDTH};
    coord = {2 * TILE_WIDTH, 5 * TILE_HEIGHT, 0, 0};
    Uint32 color = SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(image, SDL_TRUE, color);
    damage = 10;
    last_frame = 0;

    for(int i = 0; i < 4; i++)
    {
        frames[i].w = frames[i].h = TILE_WIDTH;
        frames[i].x = i * TILE_WIDTH;
        frames[i].y = 0;
    }
}

SDL_Rect Enemy::move(SDL_Surface* screen) {
    srand(time(NULL));
    int direction = rand() % 4 + 1;
    SDL_Rect temp = {0, 0, 0, 0};

    temp.w = direction - 1;

    switch(direction) {
        // move up
        case 1:
            temp.y = -1;
            break;
        // move right
        case 2:
            temp.x = 1;
            break;
        // move down
        case 3:
            temp.y = 1;
            break;
        // move left
        default:
            temp.x = -1;
            break;
    }
    last_frame = temp.w;
    return temp;
}

void Enemy::draw(SDL_Surface* screen)
{
    SDL_BlitSurface(image, &frames[last_frame], screen, &coord);
}

Enemy::~Enemy(){
    SDL_FreeSurface(image);
    image = NULL;
}
