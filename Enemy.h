#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <SDL.h>

class Enemy {
public:
    // unique enemy ID
    unsigned int id;
    unsigned int damage;

    // enemy's coordinates on the board
    SDL_Rect coord;

    // the original image whence we will extract the enemy
    SDL_Surface* image;

    // enemy's position within the image
    SDL_Rect position;

    Enemy();

    // the enemy will move randomly
    SDL_Rect move(SDL_Surface* screen);
    void draw(SDL_Surface* screen);

    ~Enemy();
};



#endif
