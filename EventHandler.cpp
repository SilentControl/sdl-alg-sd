#include "EventHandler.h"
#include "GameShell.h"
#include <iostream>

EventHandler::EventHandler()
{
    direction.x = direction.y = 0;
    quit = false;
    use_item = false;
    right_inv_arrow = false;
    left_inv_arrow = false;
}

EventHandler::~EventHandler()
{
}

void EventHandler::reset()
{
    direction.x = direction.y = 0;
    use_item = false;
    left_inv_arrow = right_inv_arrow = false;
}

void EventHandler::handleEvents()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            quit = true;
        }

        else
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_UP:
                    direction.x = 0;
                    direction.y = -1;
                    break;
                case SDLK_DOWN:
                    direction.x = 0;
                    direction.y = 1;
                    break;
                case SDLK_RIGHT:
                    direction.x = 1;
                    direction.y = 0;
                    break;
                case SDLK_LEFT:
                    direction.x = -1;
                    direction.y = 0;
                    break;
                case SDLK_q:
                    quit = true;
                    break;
                default:
                    direction.x = 0;
                    direction.y = 0;
                    break;
            }
        }

        else
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x = event.motion.x;
            int y = event.motion.y;
            std::cout << "X = " << x << " " << "Y = " << y << "\n";
            if(x >= 14 * TILE_WIDTH && x < 15 * TILE_WIDTH && y >= 0 && y < TILE_HEIGHT)
                use_item = true;
            else
            if(x >= 13 * TILE_WIDTH && x < 14 * TILE_WIDTH && y >= 0 && y < TILE_HEIGHT)
                left_inv_arrow = true;
            else
            if(x >= 15 * TILE_WIDTH && x < 16 * TILE_WIDTH && y >= 0 && y < TILE_HEIGHT)
                right_inv_arrow = true;
        }
    }
}

bool EventHandler::exitGame()
{
    return quit;
}
