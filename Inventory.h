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

    LinkedList();
    void insert (Item* val);
    void Delete (Item* val);
    void Print();
    ~LinkedList();
};

#endif
