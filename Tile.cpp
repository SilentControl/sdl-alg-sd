#include "Tile.h"

Tile::Tile(int x, int y) {
    coord.x = x;
    coord.y = y;
    coord.w = TILE_WIDTH;
    coord.h = TILE_HEIGHT;

    item = false;
    transparency = false;
    marked = false;
    previous = NULL;
}

bool Tile::hasItem() {
    return item;
}

void Tile::setItem(bool item) {
    this->item = item;
}

bool Tile::isTransparent() {
    return transparency;
}

void Tile::setTransparency (bool transparency) {
    this->transparency = transparency;
}

int Tile::getLayer() {
    return id / ((SCREEN_HEIGHT / TILE_HEIGHT) * (SCREEN_WIDTH / TILE_WIDTH));
}

Tile::~Tile()
{
    delete previous;
}
