#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#include <QObject>
#include "Buffer.h"
class BufferManager : QObject
{
    Q_OBJECT

public:
    explicit BufferManager(QObject *parent = nullptr);
    static size_t blockSize();
};

inline size_t BufferManager::blockSize()
{
    return Buffer::blockSize();
}


#endif
