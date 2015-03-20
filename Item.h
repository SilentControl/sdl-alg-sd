#ifndef _ITEM_H_
#define _ITEM_H_
#include <SDL2/SDL.h>
class Player;
struct Item
{
	SDL_Surface* image;
	int type;
	virtual void use(Player& player) = 0;
	virtual ~Item();
	virtual void draw(SDL_Surface* screen, SDL_Rect& dest) = 0;
};
#endif
