#ifndef _COLLISIONDETECTOR_H_
#define _COLLISIONDETECTOR_H_
#include <SDL.h>
#include <vector>

struct CollisionDetector
{
	CollisionDetector();
	~CollisionDetector();
	bool detect(SDL_Rect& playerPos, SDL_Rect& direction, std::vector<int>& tiles);
};

#endif
