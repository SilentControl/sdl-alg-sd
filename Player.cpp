#include "Player.h"
#include "GameShell.h"

Player::Player(){
    image = SDL_LoadBMP("hostages.bmp");
    position = {0, 0, TILE_HEIGHT, TILE_WIDTH};
    coord = {0, 0, 0, 0};
    Uint32 color = SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(image, SDL_TRUE, color);
}

void Player::move(SDL_Rect direction, SDL_Surface* screen) {
    coord.x += direction.x * TILE_WIDTH;
    coord.y += direction.y * TILE_HEIGHT;
    SDL_BlitSurface(image, &position, screen, &coord);
}

void Player::draw(SDL_Surface* screen)
{
    SDL_BlitSurface(image, &position, screen, &coord);
}

Player::~Player(){
    SDL_FreeSurface(image);
    image = NULL;
}
