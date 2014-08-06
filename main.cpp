#include "GameShell.h"
#include "EventHandler.h"
#include "Player.h"
#include "CollisionDetector.h"
#include <fstream>
#include <iostream>

int main(int argc, char* args[])
{
    GameShell game;
    Player bob;
    CollisionDetector col;
    game.loadMap();
    bob.draw(game.screen);
    game.refresh();

    EventHandler actions;
    while(true)
    {
        actions.handleEvents();
        if(actions.exitGame() == true)
        {
            break;
        }
        else
        if(actions.direction.x != 0 || actions.direction.y != 0)
        {
            if(col.detect(bob.coord, actions.direction, game.tiles) == false)
            {
                game.repaintTile(bob.coord);
                bob.move(actions.direction, game.screen);
                game.refresh();
            }
            actions.resetDirection();
        }
    }
	return 0;
}
