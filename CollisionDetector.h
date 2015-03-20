#ifndef _COLLISIONDETECTOR_H_
#define _COLLISIONDETECTOR_H_
#include <SDL.h>
#include <vector>
#include "Tile.h"
#include "Gameshell.h"

class Tile;

struct CollisionDetector
{
	CollisionDetector();
	~CollisionDetector();
	bool detect(SDL_Rect& playerPos, SDL_Rect& direction, std::vector<std::vector<Tile*> >& tiles);
};

#endif
