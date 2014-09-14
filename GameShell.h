#ifndef _GAMESHELL_H_
#define _GAMESHELL_H_
#include <SDL.h>
#include <vector>
#include <map>
#include <queue>
#include "Player.h"
#include "CollisionDetector.h"
#include "EventHandler.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Tile.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int BAR_WIDTH = 100;
const int FPS = 30;
const int MAXTILES = 300;
const int TRANSPARENCY = 9;

class Tile;
struct CollisionDetector;

struct GameShell
{
    unsigned int layerNumber;
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* tileset;
    SDL_Surface* gameover;
    SDL_Surface* lifebar;
    std::map<int, SDL_Rect> bkgtiles;
    std::vector<SDL_Rect> bartype;
    std::vector<std::vector<Tile*> > tiles;
    std::vector<int> itemlist;
    Player bob;
    CollisionDetector* col;
    EventHandler actions;
    Enemy zombie;

    GameShell();
    ~GameShell();
    void loadMap();
    void refresh();
    void repaintTile(SDL_Rect& coord);
    void action();
    bool deductHealth(unsigned int value);
    bool isItem(int value);
    void updateLifebar(SDL_Surface* screen);
    void gameOver();
    Tile* findPath(Tile*& start, Tile*& goal);
    void mark();

};

#endif
