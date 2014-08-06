#include "CollisionDetector.h"
#include "GameShell.h"

CollisionDetector::CollisionDetector()
{

}

CollisionDetector::~CollisionDetector()
{

}

bool CollisionDetector::detect(SDL_Rect& playerPos, SDL_Rect& direction, std::vector<int>& tiles)
{
	int index = (playerPos.x + TILE_WIDTH * direction.x) / TILE_WIDTH + (playerPos.y + TILE_HEIGHT * direction.y) / TILE_HEIGHT * 20;
	if(tiles[index] == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Comment