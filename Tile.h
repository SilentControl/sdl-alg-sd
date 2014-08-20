#ifndef _TILE_H_
#define _TILE_H_
#include <SDL.h>
#include "Gameshell.h"

class Tile {
    bool transparency;
    bool item;
public:
    SDL_Rect coord;
    int id;

    Tile(SDL_Surface* image, int x, int y);
    bool hasItem();
    void setItem(bool item);
    bool isTransparent();
    void setTransparency (bool transparency);
    int getLayer();
    ~Tile();
};

#endif
