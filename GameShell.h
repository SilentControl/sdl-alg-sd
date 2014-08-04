#ifndef _GAMESHELL_H_
#define _GAMESHELL_H_H
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

struct GameShell
{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* background;

    GameShell();
    ~GameShell();
    void loadMap();
    void refresh();
    void repaintTile(SDL_Rect coord);
};

#endif
