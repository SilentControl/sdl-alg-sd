#include "Inventory.h"

Node::Node() {}
Node::~Node() {}

Node* LinkedList::cursor = NULL;

LinkedList::LinkedList(){
    head = NULL;
    cursor = new Node();
}

void LinkedList::insert (Item* val) {
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

void LinkedList::Delete () {
    Node* temp = cursor;

    if (temp == NULL)
        return;
    else if (temp == head && head->next == NULL)
        cursor = head = NULL;
    else if (temp->next == NULL) {
        cursor = cursor->prev;
        temp->prev->next = NULL;
        delete temp;
    }
    else if (temp == head) {
        cursor = cursor->next;
        head->next->prev = NULL;
        head = head->next;
        delete temp;
    }
    else {
        cursor = cursor->next;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
    }
}

void LinkedList::Print() {
/*    Node *temp = head;

    while(temp != NULL) {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
*/
}

LinkedList::~LinkedList() {
    Node* prev;
    while (head) {
        prev = head;
        head = head->next;
        delete prev;
    }
    delete cursor;
}

Inventory::Inventory() {
    cursor = new Node();
}

void Inventory::updateCursor() {
    cursor = LinkedList::cursor;
}

void Inventory::moveLeft() {
    if (LinkedList::cursor->prev != NULL)
        LinkedList::cursor = LinkedList::cursor->prev;
    updateCursor();
}

void Inventory::moveRight() {
    if (LinkedList::cursor->next != NULL)
        LinkedList::cursor = LinkedList::cursor->next;
    updateCursor();
}

Inventory::~Inventory() {
    delete cursor;
}
