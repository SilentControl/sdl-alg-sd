#ifndef _ARMOR_H_
#define _ARMOR_H_
#include "Item.h"

struct Armor : public Item {
    unsigned int attacks;
	Armor();
	~Armor();
	void use(Player& player);
	void draw(SDL_Surface* screen, SDL_Rect& dest);
};

#endif
