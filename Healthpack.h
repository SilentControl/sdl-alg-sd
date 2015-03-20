#ifndef _HEALTHPACK_H_
#define _HEALTHPACK_H_
#include "Item.h"

struct Healthpack : public Item
{
	unsigned int heal;
	Healthpack();
	~Healthpack();
	void use(Player& player);
	void draw(SDL_Surface* screen, SDL_Rect& dest);
};

#endif