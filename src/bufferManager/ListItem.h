#ifndef LISTITEM_H
#define LISTITEM_H

#include "Buffer.h"
class List;
class ListItem
{
    friend class List;
    Buffer *Item;
    List *Parent;
    ListItem *Prev;
    ListItem *Next;
private:
    ListItem(List *parent, Buffer *item, ListItem *prev = nullptr,
             ListItem *next = nullptr);
    ListItem *next();
    ListItem *prev();
    void setNext(ListItem *next);
    void setPrev(ListItem *prev);
public:
    Buffer *item();
    ~ListItem();
};

inline ListItem::ListItem(List *parent, Buffer *item,
                          ListItem *prev, ListItem* next)
    :Item(item),Parent(parent),Prev(prev),Next(next)
{}

inline ListItem *ListItem::next()
{
    return Next;
}

inline ListItem *ListItem::prev()
{
    return Prev;
}

inline void ListItem::setNext(ListItem *next)
{
    Next = next;
}

inline void ListItem::setPrev(ListItem *prev)
{
    Prev = prev;
}

inline Buffer *ListItem::item()
{
    return Item;
}

inline ListItem::~ListItem()
{
    delete Item;
}

#endif // LISTITEM_H
