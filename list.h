#ifndef DOUBLY_LINKED_H_
#define DOUBLY_LINKED_H_
#include <iostream>
#include <string>
using namespace std;

struct Node
{
    Node *next;
    Node *previous;
    int data;
};
class List
{
public:
    List();
    List(const List& parent_list);
    ~List();
    bool InsertItem(int value);
    bool RemoveItem(int value);
    bool Push(int value);
    bool Pop();
    List& operator=(const List& parent_list);
    friend ostream &operator<<(ostream &stream, const List &rhs);

private:
    Node *tail_ptr_;
    Node *head_ptr_;
};
#endif
