#include "Inventory.h"

Node::Node() {}
Node::~Node() {}

LinkedList::LinkedList(){
    head = NULL;
}

void LinkedList::insert (Item* val) {
    if (head == NULL)
    {
        head = new Node();
        head->val = val;
        head->next = head->prev = NULL;
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

void LinkedList::Delete (Item* val) {
    Node* temp = head;

    while( temp && val != temp->val) {
        temp = temp->next;
    }

    if (temp == NULL)
        return;
    else if (temp == head && head->next == NULL)
        head = NULL;
    else if (temp->next == NULL) {
        temp->prev->next = NULL;
        delete temp;
    }
    else if (temp == head) {
        head->next->prev = NULL;
        head = head->next;
        delete temp;
    }
    else {
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
}
