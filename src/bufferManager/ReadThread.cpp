#include "ReadThread.h"
#include "BufferManager.h"

void ReadThread::run()
{
    while(true)
    {
        Mutex.lock();
        Buffer::pos_type pos = CurrentPos += Buffer::bufferSize();
        File *file = CurrentFile;
        Mutex.unlock();
        if(!file->IsEnd(pos) && !file->Exist(pos))
            BufferManager::bufferManager().buff(file, pos);
    }
    quit();
}
