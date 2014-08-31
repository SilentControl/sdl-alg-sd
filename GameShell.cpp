#include <SDL.h>
#include "GameShell.h"
#include "Healthpack.h"
#include "Inventory.h"
#include "Armor.h"
#include <fstream>
#include <iostream>
#include <vector>

GameShell::GameShell()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("sdl-alg-sd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    tileset = SDL_LoadBMP("tileset.bmp");
    lifebar = SDL_LoadBMP("lifebar.bmp");
    gameover = SDL_LoadBMP("gover.bmp");

    Uint32 color = SDL_MapRGB(lifebar->format, 0xFF, 0x00, 0xFF);
    SDL_SetColorKey(lifebar, SDL_TRUE, color);
    SDL_SetColorKey(gameover, SDL_TRUE, color);
    SDL_SetColorKey(tileset, SDL_TRUE, color);
    SDL_Rect tile;
    tile.x = tile.y = 0;
    tile.w = tile.h = TILE_HEIGHT;

    for(int i = 0; i < 11; i++)
    {
        bkgtiles[i] = tile;
        tile.x += TILE_WIDTH;
    }

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

    col = new CollisionDetector();
    itemlist.push_back(10); // 8 = medkit
    itemlist.push_back(8); // 10 = armor
}

GameShell::~GameShell()
{
    SDL_FreeSurface(lifebar);
    SDL_FreeSurface(gameover);
    SDL_FreeSurface(tileset);
    delete col;
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
    int nr, id = 1;
    mapfile >> layerNumber;
    std::vector<Tile*> layer;

    for(unsigned int i = 0; i < layerNumber; i++)
    {
        destile.x = -TILE_WIDTH;
        destile.y = 0;
        layer.clear();
        for(int j = 0; j < MAXTILES; j++)
        {
            mapfile >> nr;
            srctile = bkgtiles[nr];
            destile.x += TILE_WIDTH;

            Tile* tile = new Tile(destile.x, destile.y);
            tile->id = id++;
            tile->type = nr;

            if(nr == TRANSPARENCY)
            {
                tile->setTransparency(true);
            }

            if(isItem(nr) == true)
            {
                tile->setItem(true);
                if(nr == 8)
                    tile->object = new Healthpack();
                else
                    tile->object = new Armor();
            }

            layer.push_back(tile);

            SDL_BlitSurface(tileset, &srctile, screen, &destile);
            if(destile.x >= SCREEN_WIDTH - TILE_WIDTH)
            {
                destile.y += TILE_WIDTH;
                destile.x = -TILE_WIDTH;
            }
        }
        tiles.push_back(layer);
    }
    mapfile.close();
    SDL_UpdateWindowSurface(window);
}

void GameShell::repaintTile(SDL_Rect& coord)
{
    // tiles[i]; i = 20 * Y + X;
    //(tiles[i][(coord.x / TILE_WIDTH) + 20 * (coord.y / TILE_HEIGHT)])->type
    for(unsigned int i = 0; i < layerNumber; i++)
        SDL_BlitSurface(tileset, &bkgtiles[(tiles[i][(coord.x / TILE_WIDTH) + 20 * (coord.y / TILE_HEIGHT)])->type], screen, &coord);
}

void GameShell::action()
{
    loadMap();
    bob.draw(screen);
    zombie.draw(screen);
    updateLifebar(screen);
    refresh();
    bool playing = true; // is the player alive?
    while(true)
    {
        int start = SDL_GetTicks();
        actions.handleEvents();
        if(playing == false)
        {
            if(actions.exitGame() == true)
            {
                break;
            }
        }
        else
        {
            if(actions.exitGame() == true)
            {
                break;
            }

            else
            if(actions.direction.x != 0 || actions.direction.y != 0)
            {
                if(col->detect(bob.coord, actions.direction, tiles) == false)
                {
                    repaintTile(bob.coord);
                    bob.move(actions.direction, screen);
                    SDL_Rect temp = zombie.move(screen);
                    repaintTile(zombie.coord);

                    if (col->detect(zombie.coord, temp, tiles) == false)
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
                }

                refresh();
            }

            else
            {
                if(actions.use_item == true)
                {
                    bob.inventory.head->val->use(bob);
                    bob.inventory.draw(bkgtiles, tileset, screen, 9);
                }

                if(actions.left_inv_arrow == true)
                {
                    bob.inventory.moveLeft();
                    bob.inventory.draw(bkgtiles, tileset, screen, 9);
                }

                if(actions.right_inv_arrow == true)
                {
                    bob.inventory.moveRight();
                    bob.inventory.draw(bkgtiles, tileset, screen, 9);
                }

                refresh();

                int layer_numb = layerNumber - 1;
                int tile_numb = bob.coord.y / 32 * 20 + (bob.coord.x / 32);
                if((tiles[layer_numb][tile_numb])->hasItem() == true)
                {
                    bob.pick(tiles[layer_numb][tile_numb]);

                    delete (tiles[layer_numb][tile_numb])->object;
                    (tiles[layer_numb][tile_numb])->object = NULL;
                    int type = (tiles[layer_numb][tile_numb])->type;
                    (tiles[layer_numb][tile_numb])->type = TRANSPARENCY;

                    repaintTile((tiles[layer_numb][tile_numb])->coord);
                    bob.draw(screen);

                    SDL_Rect dest;
                    dest.x = 14 * TILE_WIDTH;
                    dest.y = 0;
                    repaintTile(dest);

                    bob.inventory.draw(bkgtiles, tileset, screen, type);

                    std::cout<<sizeof(SDL_Surface*);
                    refresh();
                }
            }

            actions.reset();
        }

        if(bob.health <= 0 && playing == true)
        {
            SDL_Rect bloodpos;
            bloodpos.x = bloodpos.y = 0;
            bloodpos.w = bloodpos.h = TILE_HEIGHT;
            repaintTile(zombie.coord);
            zombie.draw(screen);
            SDL_BlitSurface(tileset, &bkgtiles[5], screen, &zombie.coord);
            gameOver();
            playing = false;
            refresh();
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

void GameShell::gameOver()
{
    SDL_Rect fullscreen;
    SDL_Rect position;
    SDL_Rect goverpos;
    fullscreen.x = fullscreen.y = 0;
    fullscreen.h = SCREEN_HEIGHT;
    fullscreen.w = SCREEN_WIDTH;
    //Uint32 color = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    //SDL_FillRect(screen, &fullscreen, color);
    Uint8 alpha = 1;
    SDL_SetSurfaceBlendMode(screen, SDL_BLENDMODE_BLEND);
    SDL_SetSurfaceAlphaMod(screen, alpha);
    position.x = 80;
    position.y = 212;
    goverpos.x = goverpos.y = 0;
    goverpos.h = 55;
    goverpos.w = 480;
    SDL_BlitSurface(gameover, &goverpos, screen, &position);
}

bool GameShell::isItem(int value)
{
    for(unsigned int i = 0; i < itemlist.size(); i++)
    {
        if(itemlist[i] == value)
        {
            return true;
        }
    }
    return false;
}
