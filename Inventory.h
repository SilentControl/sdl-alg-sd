#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "Item.h"

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
    ~Inventory();
};

#endif
