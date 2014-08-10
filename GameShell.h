#ifndef _GAMESHELL_H_
#define _GAMESHELL_H_H
#include <SDL.h>
#include <vector>
#include "Player.h"
#include "CollisionDetector.h"
#include "EventHandler.h"
#include "Enemy.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int BAR_WIDTH = 100;
const int FPS = 30;

struct GameShell
{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* background;
    SDL_Surface* gameover;
    SDL_Surface* blood;
    // the player's lifebar
    SDL_Surface* lifebar;
    std::vector<SDL_Rect> bkgtiles;
    std::vector<int> tiles;
    std::vector<SDL_Rect> bartype;
    Player bob;
    CollisionDetector col;
    EventHandler actions;
    Enemy zombie;

    GameShell();
    ~GameShell();
    void loadMap();
    void refresh();
    void repaintTile(SDL_Rect& coord);
    void action();
    bool deductHealth(unsigned int value);
    void updateLifebar(SDL_Surface* screen);
    void gameOver();
};

#endif
