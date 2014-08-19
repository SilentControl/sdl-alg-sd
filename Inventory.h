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

class LinkedList {
public:
    Node* head;
    static Node* cursor;

    LinkedList();
    void insert (Item* val);
    void Delete ();
    void Print();
    ~LinkedList();
};

class Inventory {
    LinkedList menu;
    Node* cursor;

    Inventory();
    void updateCursor();
    void moveLeft();
    void moveRight();
    ~Inventory();
};

#endif
