#include "BufferManager.h"


BufferManager::BufferManager(QObject *parent)
    :QObject(parent)
{

}

BufferManager &BufferManager::bufferManager()
{
    static BufferManager bm;
    return bm;
}
