#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "Item.h"
#include <SDL.h>
#include <map>

struct Item;
class Player;

class Node {
public:
    Item* val;
    Node* next;
    Node* prev;
    Node();
    ~Node();
};

class Inventory {
public:
    Node* head;
    Node* cursor;

    Inventory();
    void insert (Item* val);
    void Delete ();
    void Print();
    void moveLeft(std::map<int, SDL_Rect>& bkgtiles, SDL_Surface*& tileset, SDL_Surface*& screen);
    void moveRight(std::map<int, SDL_Rect>& bkgtiles, SDL_Surface*& tileset, SDL_Surface*& screen);
    void draw(std::map<int, SDL_Rect>& bkgtiles, SDL_Surface*& tileset, SDL_Surface*& screen, int type);
    ~Inventory();
};

#endif
