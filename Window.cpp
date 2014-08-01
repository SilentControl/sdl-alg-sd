/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <cstdio>
#include <bitset>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

SDL_Window* window = 0;
SDL_Surface* screen = 0;
SDL_Surface* image = 0;
SDL_Surface* player = 0;
SDL_Rect srctile; //= {23, 33, TILE_WIDTH, TILE_HEIGHT};
SDL_Rect destile; //= {0, 0, TILE_WIDTH, TILE_HEIGHT};

struct Direction
{
    int x;
    int y;
};

void init()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("sdl-alg-sd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
}

void loadMedia()
{
    image = SDL_LoadBMP("cs2dnorm.bmp");
    player = SDL_LoadBMP("hostages.bmp");
    srctile.x = 0;
    srctile.y = 5 * TILE_HEIGHT;
    srctile.w = srctile.h = TILE_HEIGHT;

    destile.x = 0;
    destile.y = -TILE_WIDTH;

    std::bitset<1> flag;
    flag = 0;

    for(int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
    {
        if(i % 20 == 0)
        {
            destile.x = 0;
            destile.y += TILE_HEIGHT;
            flag = ~flag;
        }

        else
        {
            destile.x += TILE_WIDTH;
        }

        if(flag == 0)
        {
            if(i % 2 == 0)
            {
                srctile.x = 0;
                srctile.y = 5 * TILE_HEIGHT;
                srctile.w = srctile.h = TILE_HEIGHT;
                SDL_BlitSurface(image, &srctile, screen, &destile);
            }

            else
            {
                srctile.x = 0;
                srctile.y = 6 * TILE_HEIGHT;
                srctile.w = srctile.h = TILE_HEIGHT;
                SDL_BlitSurface(image, &srctile, screen, &destile);
            }
        }

        else
        {
            if(i % 2 != 0)
            {
                srctile.x = 0;
                srctile.y = 5 * TILE_HEIGHT;
                srctile.w = srctile.h = TILE_HEIGHT;
                SDL_BlitSurface(image, &srctile, screen, &destile);
            }

            else
            {
                srctile.x = 0;
                srctile.y = 6 * TILE_HEIGHT;
                srctile.w = srctile.h = TILE_HEIGHT;
                SDL_BlitSurface(image, &srctile, screen, &destile);
            }
        }
    }

    srctile.x = srctile.y = 0;
    destile.x = 9 * TILE_WIDTH;
    destile.y = 14 * TILE_HEIGHT;

    // transparency
    Uint32 color = SDL_MapRGB(player->format, 0xff, 0x00, 0xff);
    SDL_SetColorKey(player, SDL_TRUE, color);
    SDL_BlitSurface(player, &srctile, screen, &destile);
    SDL_UpdateWindowSurface(window);
}

void close()
{
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


int main(int argc, char* args[])
{
    init();
    loadMedia();

    bool running = true;
    SDL_Event event;
    Direction direction;
    direction.x = 0;
    direction.y = 0;
    Direction position;
    position.x = 9 * TILE_WIDTH;
    position.y = 14 * TILE_WIDTH;
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
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
                    default:
                        direction.x = 0;
                        direction.y = 0;
                        break;
                }
            }
        }

        SDL_Rect tilecolor;
        SDL_Rect playerpos;
        if(direction.x != 0 || direction.y != 0)
        {
            if((position.y / TILE_HEIGHT) % 2 == 0)
            {
                if((position.x / TILE_WIDTH) % 2 == 0)
                {
                    tilecolor.x = 0;
                    tilecolor.y = 6 * TILE_HEIGHT;
                    tilecolor.w = tilecolor.h = TILE_WIDTH;
                }

                else
                {
                    tilecolor.x = 0;
                    tilecolor.y = 5 * TILE_HEIGHT;
                    tilecolor.w = tilecolor.h = TILE_WIDTH;
                }
            }

            else
            {
                if((position.x / TILE_WIDTH) % 2 != 0)
                {
                    tilecolor.x = 0;
                    tilecolor.y = 6 * TILE_HEIGHT;
                    tilecolor.w = tilecolor.h = TILE_WIDTH;
                }

                else
                {
                    tilecolor.x = 0;
                    tilecolor.y = 5 * TILE_HEIGHT;
                    tilecolor.w = tilecolor.h = TILE_WIDTH;
                }
            }

            playerpos.x = position.x;
            playerpos.y = position.y;
            printf("X = %d, Y = %d\n", position.x, position.y);
            SDL_BlitSurface(image, &tilecolor, screen, &playerpos);
            position.x += direction.x * TILE_WIDTH;
            position.y += direction.y * TILE_HEIGHT;
            playerpos.x = position.x;
            playerpos.y = position.y;
            srctile.x = srctile.y = 0;
            srctile.w = srctile.h = TILE_WIDTH;
            SDL_BlitSurface(player, &srctile, screen, &playerpos);
            SDL_UpdateWindowSurface(window);
            direction.x = direction.y = 0;
        }
    }
    close();
	return 0;
}
