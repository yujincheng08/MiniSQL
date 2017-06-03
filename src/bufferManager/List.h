#ifndef LIST_H
#define LIST_H
#include "ListItem.h"
#include <iostream>

class List
{
    ListItem *head;
    ListItem *tail;
    size_t Size;
public:
    List();
    void insert(Buffer *buffer);
    void top(ListItem *item);
    void relaseLast();
    size_t size();
};

inline List::List()
    :head(new ListItem(this,nullptr)),tail(head)
{}

inline void List::insert(Buffer *buffer)
{
    ++Size;
    tail->setNext(new ListItem(this,buffer,tail));
    tail = tail->next();
}

inline void List::top(ListItem *item)
{
    item->next()->setPrev(item->prev());
    item->prev()->setNext(item->next());
    item->setNext(head->next());
    head->setNext(item);
}

inline void List::relaseLast()
{
    if(tail==head) return;
    --Size;
    ListItem *last = tail;
    tail = tail->prev();
    delete last;
}

inline size_t List::size()
{
    return Size;
}

#endif // LIST_H
