#include "WriteThread.h"

void WriteThread::run()
{
    while(!WriteList.empty())
    {
        Mutex.lock();
        auto i = WriteList.front();
        i->write();
        WriteList.pop_front();
        Mutex.unlock();
    }
    quit();
}
