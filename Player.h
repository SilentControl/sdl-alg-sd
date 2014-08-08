#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SDL.h>
#include <vector>

class Player {
public:
    // unique player ID
    unsigned int id;

    // health
    unsigned int health;

    // player's coordinates on the board
    SDL_Rect coord;

    // the original image whence we will extract the player
    SDL_Surface* image;
/*
    // the player's lifebar
    SDL_Surface* lifebar;
*/
    // player's position within the image
    SDL_Rect position;
/*
    std::vector<SDL_Rect> bartype;
*/
    Player();

    // the player will be moved towards the new coordinates
    void move(SDL_Rect& direction, SDL_Surface* screen);
    void draw(SDL_Surface* screen);
    /*
    bool deductHealth(unsigned int value);
    void updateLifebar(SDL_Surface* screen);
    */
    ~Player();
};

#endif
