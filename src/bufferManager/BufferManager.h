#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "Buffer.h"
#include "List.h"
#include <QObject>
#include <unordered_map>

class BufferManager : public QObject
{
    Q_OBJECT
private:
    std::unordered_map<std::string, ListItem*>
        HashMap;
    List list;
public:
    explicit BufferManager(QObject *parent = nullptr);
    static size_t blockSize();
};

inline size_t BufferManager::blockSize()
{
    return Buffer::blockSize();
}

#endif
