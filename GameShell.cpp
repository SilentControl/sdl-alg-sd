#include <SDL.h>
#include "GameShell.h"
#include <fstream>
#include <iostream>
#include <vector>

GameShell::GameShell()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("sdl-alg-sd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    background = SDL_LoadBMP("cs2dnorm.bmp");
    SDL_Rect tile;
    tile.y = 0;
    tile.w = tile.h = TILE_HEIGHT;
    tile.x = 10 * TILE_WIDTH;
    bkgtiles.push_back(tile);
    tile.x = 11 * TILE_WIDTH;
    bkgtiles.push_back(tile);
    tile.x = 14 * TILE_WIDTH;
    tile.y = 6 * TILE_HEIGHT;
    bkgtiles.push_back(tile);
}

GameShell::~GameShell()
{
    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameShell::refresh()
{
    SDL_UpdateWindowSurface(window);
}

void GameShell::loadMap()
{
    SDL_Rect srctile, destile;
    std::ifstream mapfile("map.txt");
    int nr;

    destile.x = -TILE_WIDTH;
    destile.y = 0;
    while(mapfile >> nr)
    {
        tiles.push_back(nr);
        srctile = bkgtiles[nr];
        destile.x += TILE_WIDTH;
        SDL_BlitSurface(background, &srctile, screen, &destile);
        if(destile.x >= SCREEN_WIDTH - TILE_WIDTH)
        {
            destile.y += TILE_WIDTH;
            destile.x = -TILE_WIDTH;
        }
    }
    mapfile.close();
    SDL_UpdateWindowSurface(window);
}

void GameShell::repaintTile(SDL_Rect& coord)
{
    // tiles[i]; i = 20 * Y + X;
    SDL_BlitSurface(background, &bkgtiles[tiles[(coord.x / TILE_WIDTH) + 20 * (coord.y / TILE_HEIGHT)]], screen, &coord);
}

void GameShell::action()
{
    loadMap();
    bob.draw(screen);
    zombie.draw(screen);
    bob.updateLifebar(screen);
    refresh();
    while(true)
    {
        int start = SDL_GetTicks();
        actions.handleEvents();
        if(actions.exitGame() == true)
        {
            break;
        }
        else
        if(actions.direction.x != 0 || actions.direction.y != 0)
        {
            if(col.detect(bob.coord, actions.direction, tiles) == false)
            {
                repaintTile(bob.coord);
                bob.move(actions.direction, screen);
                SDL_Rect temp = zombie.move(screen);
                repaintTile(zombie.coord);

                if (col.detect(zombie.coord, temp, tiles) == false)
                {
                    zombie.coord.x += temp.x * TILE_WIDTH;
                    zombie.coord.y += temp.y * TILE_HEIGHT;
                }
                zombie.draw(screen);
                bob.draw(screen);

                // zombie attacks the player
                if(bob.coord.x == zombie.coord.x && bob.coord.y == zombie.coord.y)
                {
                    bob.deductHealth(zombie.damage);
                    // repair the 3 tiles which are under the lifebar
                    SDL_Rect repair;
                    repair.x = SCREEN_WIDTH / 2;
<<<<<<< HEAD
                    repair.y = SCREEN_HEIGHT - 20;
=======
                    repair.y = 0;
>>>>>>> upstream/master
                    for(int i = 0; i < 4; i++)
                    {
                        repaintTile(repair);
                        repair.x += TILE_WIDTH;
                    }

                    // update the player's lifebar
                    bob.updateLifebar(screen);
                }

                refresh();
            }
            actions.resetDirection();
        }

		if(1000/FPS > SDL_GetTicks() - start)
		{
			SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
    }
}
