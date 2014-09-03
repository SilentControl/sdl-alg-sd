#include "Healthpack.h"
#include "GameShell.h"
#include <iostream>

Healthpack::Healthpack()
{
    type = 8;
	heal = 10;
	image = SDL_LoadBMP("medikit.bmp");
}

Healthpack::~Healthpack()
{
	SDL_FreeSurface(image);
}

void Healthpack::use(Player& player)
{
	player.health = (player.health + heal) % 101;
	std::cout<<"HEALTH = " << player.health<<"\n";
}

void Healthpack::draw(SDL_Surface* screen, SDL_Rect& dest)
{
	SDL_Rect position;
	position.x = position.y = 0;
	position.w = position.h = TILE_WIDTH;
	SDL_BlitSurface(image, &position, screen, &dest);
}
