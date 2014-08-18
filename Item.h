#ifndef _ITEM_H_
#define _ITEM_H_
#include <SDL.h>
#include "Player.h"

struct Item
{
	SDL_Surface* image;
	virtual void use(Player& player) = 0;
	virtual ~Item();
	virtual void draw(SDL_Surface* screen, SDL_Rect& dest) = 0;
};
#endif
