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
}

void Player::move(SDL_Rect& direction, SDL_Surface* screen) {
    coord.x += direction.x * TILE_WIDTH;
    coord.y += direction.y * TILE_HEIGHT;
    SDL_BlitSurface(image, &position, screen, &coord);
}

void Player::draw(SDL_Surface* screen)
{
    SDL_BlitSurface(image, &position, screen, &coord);
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
