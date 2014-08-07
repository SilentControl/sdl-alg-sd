#include "Player.h"
#include "GameShell.h"
#include <iostream>

Player::Player(){
    image = SDL_LoadBMP("hostages.bmp");
    position = {0, 0, TILE_HEIGHT, TILE_WIDTH};
    coord = {0, 0, 0, 0};
    Uint32 color = SDL_MapRGB(image->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(image, SDL_TRUE, color);

    lifebar = SDL_LoadBMP("lifebar.bmp");
    SDL_SetColorKey(lifebar, SDL_TRUE, color);
    health = 100;

    // creating life bar types
    SDL_Rect bartile;
    bartile.x = 0;
    bartile.y = 0;
    bartile.h = 20;
    bartile.w = 100;

    for(int i = 0; i < 6; i++)
    {
        bartype.push_back(bartile);
        bartile.y += 20;
    }
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

Player::~Player(){
    SDL_FreeSurface(image);
    SDL_FreeSurface(lifebar);
    image = NULL;
    lifebar = NULL;
}

bool Player::deductHealth(unsigned int value)
{
    if(health <= 0)
        return true;
    else
    {
        health -= value;
        if(health <= 0)
            return true;
        else
            return false;
    }
}

void Player::updateLifebar(SDL_Surface* screen)
{
    SDL_Rect barpos;
    barpos.x = SCREEN_WIDTH / 2;
    barpos.y = SCREEN_HEIGHT - 20; // 20 is the HEIGHT of the lifebar
    if(health <= 100 && health >= 80)
    {
        bartype[0].w = health;
        SDL_BlitSurface(lifebar, &bartype[0], screen, &barpos);
    }

    else
    if(health <= 79 && health >= 60)
    {
        bartype[1].w = health;
        SDL_BlitSurface(lifebar, &bartype[1], screen, &barpos);
    }

    else
    if(health <= 59 && health >= 40)
    {
        bartype[2].w = health;
        SDL_BlitSurface(lifebar, &bartype[2], screen, &barpos);
    }

    else
    if(health <= 39 && health >= 20)
    {
        bartype[3].w = health;
        SDL_BlitSurface(lifebar, &bartype[3], screen, &barpos);
    }

    else
    if(health <= 19 && health >= 1)
    {
        bartype[4].w = health;
        SDL_BlitSurface(lifebar, &bartype[4], screen, &barpos);
    }

    else
    if(health <= 0)
    {
        bartype[5].w = 100;
        SDL_BlitSurface(lifebar, &bartype[5], screen, &barpos);
    }
}
