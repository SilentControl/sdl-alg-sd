#include "GameShell.h"
#include "EventHandler.h"
#include "Player.h"
#include <fstream>
#include <iostream>

int main(int argc, char* args[])
{
    GameShell game;
    Player bob;
    //game.loadMap();
    game.parse();
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
            std::cout<<"CRASH1\n";
            game.repaintTile(bob.coord);
            std::cout<<"CRASH2\n";
            bob.move(actions.direction, game.screen);
            std::cout<<"CRASH3\n";
            game.refresh();
            std::cout<<"CRASH4\n";
            actions.resetDirection();
        }
    }
	return 0;
}
