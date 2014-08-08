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
    lifebar = SDL_LoadBMP("lifebar.bmp");
    Uint32 color = SDL_MapRGB(lifebar->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(lifebar, SDL_TRUE, color);
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

    // creating life bar types
    SDL_Rect bartile;
    bartile.x = 0;
    bartile.y = 0;
    bartile.h = 20;
    bartile.w = 100;

    for(int i = 0; i < 7; i++)
    {
        bartype.push_back(bartile);
        bartile.y += 20;
    }
}

GameShell::~GameShell()
{
    SDL_FreeSurface(lifebar);
    lifebar = NULL;
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
    updateLifebar(screen);
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
                    deductHealth(zombie.damage);
                    // repair the 3 tiles which are under the lifebar
                    SDL_Rect repair;
                    repair.x = (SCREEN_WIDTH - BAR_WIDTH) / 2 - 14;
                    repair.y = 0;
                    for(int i = 0; i < 4; i++)
                    {
                        repaintTile(repair);
                        repair.x += TILE_WIDTH;
                    }

                    // update the player's lifebar
                    updateLifebar(screen);
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

bool GameShell::deductHealth(unsigned int value)
{
    if(bob.health <= 0)
        return true;
    else
    {
        bob.health -= value;
        if(bob.health <= 0)
            return true;
        else
            return false;
    }
}

void GameShell::updateLifebar(SDL_Surface* screen)
{
    SDL_Rect barpos;
    barpos.x = (SCREEN_WIDTH - BAR_WIDTH) / 2;
    barpos.y = 6; // 20 is the HEIGHT of the lifebar

    if(bob.health <= 100 && bob.health >= 80)
    {
        bartype[0].w = bob.health;
        SDL_BlitSurface(lifebar, &bartype[0], screen, &barpos);
    }

    else
    if(bob.health <= 79 && bob.health >= 60)
    {
        bartype[1].w = bob.health;
        SDL_BlitSurface(lifebar, &bartype[1], screen, &barpos);
    }

    else
    if(bob.health <= 59 && bob.health >= 40)
    {
        bartype[2].w = bob.health;
        SDL_BlitSurface(lifebar, &bartype[2], screen, &barpos);
    }

    else
    if(bob.health <= 39 && bob.health >= 20)
    {
        bartype[3].w = bob.health;
        SDL_BlitSurface(lifebar, &bartype[3], screen, &barpos);
    }

    else
    if(bob.health <= 19 && bob.health >= 1)
    {
        bartype[4].w = bob.health;
        SDL_BlitSurface(lifebar, &bartype[4], screen, &barpos);
    }

    else
    if(bob.health <= 0)
    {
        bartype[5].w = 100;
        SDL_BlitSurface(lifebar, &bartype[5], screen, &barpos);
    }

    SDL_BlitSurface(lifebar, &bartype[6], screen, &barpos);
}
