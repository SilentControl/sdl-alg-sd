#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_
#include <SDL.h>

struct EventHandler
{
    SDL_Event event;
    SDL_Rect direction;
    bool quit;
    bool use_item;
    bool left_inv_arrow;
    bool right_inv_arrow;

    EventHandler();
    ~EventHandler();
    void handleEvents();
    void reset();
    bool exitGame();
};

#endif
