#include "Enemy.h"
#include "GameShell.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


Enemy::Enemy(){
    image = SDL_LoadBMP("zombie.bmp");
    position = {0, 1 * TILE_HEIGHT, TILE_HEIGHT, TILE_WIDTH};
    coord = {2 * TILE_WIDTH, 5 * TILE_HEIGHT, 0, 0};
    Uint32 color = SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(image, SDL_TRUE, color);
    damage = 10;
}

SDL_Rect Enemy::move(SDL_Surface* screen) {
    srand(time(NULL));
    int direction = rand() % 4 + 1;
    SDL_Rect temp = {0, 0, 0, 0};

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
    return temp;
}

void Enemy::draw(SDL_Surface* screen)
{
    SDL_BlitSurface(image, &position, screen, &coord);
}

Enemy::~Enemy(){
    SDL_FreeSurface(image);
    image = NULL;
}
