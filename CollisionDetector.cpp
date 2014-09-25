#include "CollisionDetector.h"
#include "GameShell.h"
#include <iostream>
CollisionDetector::CollisionDetector()
{

}

CollisionDetector::~CollisionDetector()
{

}

bool CollisionDetector::detect(SDL_Rect& playerPos, SDL_Rect& direction, std::vector<std::vector<Tile*> >& tiles)
{
    // index for the array of tiles
	int index = (playerPos.x + TILE_WIDTH * direction.x) / TILE_WIDTH + (playerPos.y + TILE_HEIGHT * direction.y) / TILE_HEIGHT * 20;
	int index_x = (playerPos.x + TILE_WIDTH * direction.x) / TILE_WIDTH;
	int index_y = (playerPos.y + TILE_HEIGHT * direction.y) / TILE_HEIGHT;

    if(index >= 0 && index < (int)tiles[0].size())
    {
        if(tiles[0][index]->type == 2)
            return true;
	}
    else if (index_x < 0 || index_x > SCREEN_WIDTH / TILE_WIDTH - 1)
    {
        return true;
    }
    else if (index_y < 0 || index_y > SCREEN_HEIGHT / TILE_HEIGHT - 1)
    {
        return true;
    }

	return false;
}

//Comment
