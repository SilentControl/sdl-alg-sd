#include "EventHandler.h"

EventHandler::EventHandler()
{
    direction.x = direction.y = 0;
    quit = false;
}

EventHandler::~EventHandler()
{
}

void EventHandler::resetDirection()
{
    direction.x = direction.y = 0;
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
    }
}

bool EventHandler::exitGame()
{
    return quit;
}
