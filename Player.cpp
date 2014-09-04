#include "Player.h"
#include "GameShell.h"
#include "Armor.h"
#include "Healthpack.h"
#include <iostream>

Player::Player(){
    image = SDL_LoadBMP("hostages.bmp");
    position = {0, 0, TILE_HEIGHT, TILE_WIDTH};
    coord = {0, 0, 0, 0};
    Uint32 color = SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(image, SDL_TRUE, color);
    health = 100;
    invulnerable = 0;
    last_frame = 0;
    for(int i = 0; i < 4; i++)
    {
        frame[i][0].w = frame[i][1].w = TILE_WIDTH;
        frame[i][0].h = frame[i][1].h = TILE_HEIGHT;

        frame[i][0].x = i * TILE_WIDTH;
        frame[i][0].y = 0;

        frame[i][1].x = i * TILE_WIDTH;
        frame[i][1].y = TILE_HEIGHT;
    }
}

void Player::move(SDL_Rect& direction, SDL_Surface* screen) {
    coord.x += direction.x * TILE_WIDTH;
    coord.y += direction.y * TILE_HEIGHT;
    last_frame = direction.w;
    SDL_BlitSurface(image, &frame[direction.w][0], screen, &coord);
}

void Player::draw(SDL_Surface* screen)
{
    SDL_BlitSurface(image, &frame[last_frame][0], screen, &coord);
}

void Player::pick(Tile*& tile) {
    if (tile->hasItem()) {
        if(tile->type == 8)
            inventory.insert(new Healthpack());
        else
            inventory.insert(new Armor());
        tile->setItem(false);
    }
}

Player::~Player(){
    SDL_FreeSurface(image);
    image = NULL;
}
