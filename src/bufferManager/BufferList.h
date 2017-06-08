#ifndef BUFFERLIST_H
#define BUFFERLIST_H

#include "BufferListItem.h"
#include <cstddef>
class BufferList
{
    friend class BufferListItem;
    BufferListItem *head;
    BufferListItem *tail;
    size_t Size;
private:
    BufferList();
    void insert(BufferListItem *item);
    void top(BufferListItem *item);
    void remove(BufferListItem *item);
    BufferListItem *last();
    const size_t &size();
};

inline BufferList::BufferList()
    :head(nullptr),tail(head)
{}

inline void BufferList::insert(BufferListItem *item)
{
    if(!head)
        head = item;
    if(!tail)
        tail = item;
    else
        tail->Next = item;
    ++Size;
}

inline void BufferList::top(BufferListItem *item)
{
    remove(item);
    item->Next = head->Next;
    head->Next = item;
}

inline void BufferList::remove(BufferListItem *item)
{
    if(item->Next)
        item->Next->Prev = item->Prev;
    if(item->Prev)
        item->Prev->Next = item->Next;
}

inline BufferListItem *BufferList::last()
{
    return tail;
}

inline const size_t &BufferList::size()
{
    return Size;
}

#endif // BUFFERLIST_H
