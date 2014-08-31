#include "Armor.h"
#include "GameShell.h"

Armor::Armor()
{
    // player will be immune to the following three enemy attacks
	attacks = 3;
	image = SDL_LoadBMP("heavyarmor_d.bmp");
}

Armor::~Armor()
{
	SDL_FreeSurface(image);
}

void Armor::use(Player& player)
{
	// TODO
}

void Armor::draw(SDL_Surface* screen, SDL_Rect& dest)
{
	SDL_Rect position;
	position.x = position.y = 0;
	position.w = position.h = TILE_WIDTH;
	SDL_BlitSurface(image, &position, screen, &dest);
}
