#include "Inventory.h"
#include "GameShell.h"

Node::Node() {}
Node::~Node() {}

Inventory::Inventory(){
    head = NULL;
    cursor = new Node();
}

void Inventory::insert (Item* val) {
    if (head == NULL)
    {
        head = new Node();
        head->val = val;
        head->next = head->prev = NULL;
        cursor = head;
    }
    else
    {
        Node* temp = new Node();
        temp->val = val;
        temp->next = head;
        head->prev = temp;
        head = temp;
    }

}

void Inventory::draw(std::map<int, SDL_Rect>& bkgtiles, SDL_Surface*& tileset, SDL_Surface*& screen, int type)
{
    SDL_Rect dest;
    dest.x = 13 * TILE_WIDTH;
    dest.y = 0;
    SDL_BlitSurface(tileset, &bkgtiles[6], screen, &dest);
    dest.x += 2 * TILE_WIDTH;
    SDL_BlitSurface(tileset, &bkgtiles[7], screen, &dest);
    dest.x -= TILE_WIDTH;
    SDL_BlitSurface(tileset, &bkgtiles[type], screen, &dest);
}


void Inventory::Delete () {
    Node* temp = cursor;

    if (temp == NULL)
        return;
    else if (temp == head && head->next == NULL)
        cursor = head = NULL;
    else if (temp->next == NULL) {
        cursor = cursor->prev;
        temp->prev->next = NULL;
    }
    else if (temp == head) {
        cursor = cursor->next;
        head->next->prev = NULL;
        head = head->next;
    }
    else {
        cursor = cursor->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    delete temp;
}

void Inventory::Print() {}

void Inventory::moveLeft() {
    if (cursor->prev != NULL)
        cursor = cursor->prev;
}

void Inventory::moveRight() {
    if (cursor->next != NULL)
        cursor = cursor->next;
}

Inventory::~Inventory() {
    Node* prev;
    while (head) {
        prev = head;
        head = head->next;
        delete prev;
    }
    delete cursor;
}
