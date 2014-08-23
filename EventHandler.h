#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_
#include <SDL.h>

struct EventHandler
{
    SDL_Event event;
    SDL_Rect direction;
    bool pick_object;
    bool quit;

    EventHandler();
    ~EventHandler();
    void handleEvents();
    void resetDirection();
    bool exitGame();
};

#endif
