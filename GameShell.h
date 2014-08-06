#ifndef _GAMESHELL_H_
#define _GAMESHELL_H_H
#include <SDL.h>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int FPS = 30;

struct GameShell
{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* background;
    std::vector<SDL_Rect> bkgtiles;
    std::vector<int> tiles;

    GameShell();
    ~GameShell();
    void loadMap();
    void refresh();
    void repaintTile(SDL_Rect& coord);
};

#endif
