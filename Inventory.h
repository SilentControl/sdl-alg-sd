#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "Item.h"
#include <SDL.h>
#include <map>

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
    void moveLeft();
    void moveRight();
    void draw(std::map<int, SDL_Rect>& bkgtiles, SDL_Surface*& tileset, SDL_Surface*& screen);
    ~Inventory();
};

#endif
