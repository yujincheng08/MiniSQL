#include "BufferListItem.h"
#include "BufferList.h"
BufferList *const BufferListItem::List = new BufferList();

BufferListItem::BufferListItem()
{
    List->insert(this);
}

void BufferListItem::top()
{
    List->top(this);
}

BufferListItem::~BufferListItem()
{
    List->remove(this);
}
