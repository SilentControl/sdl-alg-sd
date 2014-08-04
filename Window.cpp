#include <SDL.h>
#include <cstdio>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

struct GameShell
{
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Surface* background;

    GameShell();
    ~GameShell();
    void loadMap();
    void refresh();
};

struct EventHandler
{
    SDL_Event event;
    SDL_Rect direction;
    bool quit;

    EventHandler();
    ~EventHandler();
    void handleEvents();
    void resetDirection();
    bool exitGame();
};

class Player {
public:
    // unique player ID
    unsigned int id;

    // player's coordinates on the board
    int x;
    int y;

    // the original image whence we will extract the player
    SDL_Surface* image;

    // player's position within the image
    SDL_Rect position;

    Player();

    // the player will be moved towards the new coordinates
    void Move (SDL_Rect direction);

    ~Player();
};

Player::Player(){
    image = SDL_LoadBMP("hostages.bmp");
    position = {0, 0, TILE_HEIGHT, TILE_WIDTH};
}

Player::Move(SDL_Rect direction, SDL_Surface* screen) {
    x += direction.x * TILE_WIDTH;
    y += direction.y * TILE_HEIGHT;
    SDL_Rect hero_position = {x, y, TILE_HEIGHT, TILE_WIDTH};
    SDL_BlitSurface( image, &position, screen, &hero_position );
}

Player::~Player(){
    SDL_FreeSurface(image);
    image = NULL;
}


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


GameShell::GameShell()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("sdl-alg-sd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    background = SDL_LoadBMP("cs2dnorm.bmp");
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
    srctile.y = 5 * TILE_HEIGHT;
    srctile.w = srctile.h = TILE_HEIGHT;

    for (int i = 0; i < SCREEN_WIDTH / TILE_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT / TILE_HEIGHT; j++)
        {
            if ((i + j) % 2)
                srctile.x =  5 * TILE_WIDTH;
            else
                srctile.x = 4 * TILE_WIDTH;

            destile.x = i * TILE_WIDTH;
            destile.y = j * TILE_HEIGHT;
            SDL_BlitSurface(background, &srctile, screen, &destile);
        }
    }
    SDL_UpdateWindowSurface(window);
}

int main(int argc, char* args[])
{
    GameShell game;
    game.loadMap();

    EventHandler actions;
    while(true)
    {
        actions.handleEvents();
        if(actions.exitGame() == true)
        {
            break;
        }
        game.refresh();
        actions.resetDirection();
    }
	return 0;
}
