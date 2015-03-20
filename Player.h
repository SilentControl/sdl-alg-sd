#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL2/SDL.h>
#include <vector>
#include "Inventory.h"

class Inventory;
class Tile;

class Player {
public:
    // unique player ID
    unsigned int id;

    // health
    unsigned int health;
    SDL_Rect frame[4][2];

    int last_frame;

    // player's coordinates on the board
    SDL_Rect coord;

    // the original image whence we will extract the player
    SDL_Surface* image;

    SDL_Surface* basic_player;
    SDL_Surface* armored_player;

    // player's position within the image
    SDL_Rect position;

    unsigned int invulnerable;

    Inventory inventory;

    Player();

    // the player will be moved towards the new coordinates
    void move(SDL_Rect& direction, SDL_Surface* screen);
    void draw(SDL_Surface* screen);
    void pick(Tile*& tile);
    void equip_armor(bool value);
    ~Player();
};

#endif
